/**
* @file FishFinfluencer.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <string>
#include "FishFinfluencer.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename when Finfluencer is dormant
const wstring FishDormantFinfluencerImageName = L"images/finfluencer.png";

/// Fish filename when Finfluencer is active
const wstring FishActiveFinfluencerImageName = L"images/finfluencer-a.png";

/// Distance other fish traverse when Finfluencer is active
const double MoveDistance = 100;

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishFinfluencer::FishFinfluencer(Aquarium *aquarium) : Item(aquarium)
{
    mActiveImage = std::make_unique<wxImage>(FishActiveFinfluencerImageName, wxBITMAP_TYPE_ANY);
    mActiveBitmap = std::make_unique<wxBitmap>(*mActiveImage);

    mFishImage = make_unique<wxImage>(FishDormantFinfluencerImageName, wxBITMAP_TYPE_ANY);
    mFishBitmap = make_unique<wxBitmap>(*mFishImage);
}

/**
 * Draw this fish
 * @param dc Device context to draw on
 */
void FishFinfluencer::Draw(wxDC *dc)
{
    wxBitmap* bitmap = mIsActive ? mActiveBitmap.get() : mFishBitmap.get();
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();
    dc->DrawBitmap(*bitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool FishFinfluencer::HitTest(int x, int y)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mFishImage->IsTransparent((int)testX, (int)testY);
}

/** Activates the Finfluencer */
void FishFinfluencer::Active()
{
    mIsActive = true;
}

/** Deactives the Finfluencer */
void FishFinfluencer::Deactive()
{
    mIsActive = false;
}

/**
 * Moves target item in relation to the source item
 * @param source The source item
 * @param target The target item
 */
void FishFinfluencer::Move(std::shared_ptr<Item> target, std::shared_ptr<Item> source)
{
    double dx = target->GetX() - source->GetX();
    double dy = target->GetY() - source->GetY();
    double dist = sqrt(dx * dx + dy * dy);

    if (dist < MoveDistance) return;

    double factor = MoveDistance / dist;
    source->SetLocation(source->GetX() + dx * factor, source->GetY() + dy * factor);
}