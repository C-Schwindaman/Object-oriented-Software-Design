/**
 * @file Player.cpp
 * @author Caleb Blackwell
 */

#include "pch.h"
#include "Player.h"
#include "Game.h"

using namespace std;

/// Player character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for a grabbing cycle in seconds
const double GrabbingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/**
* Constructor
* @param game The game this Player belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Player
 * @param h Height of the Player
 * @param filename Filename of image1
 * @param tileHeight Height of the tile
 * @param filename2 Filename of image2
 * @param mPA Mouth pivot angle
 * @param mPX Mouth pivot X
 * @param mPY Mouth pivot Y
 * @param isChest Is it a Chest?
 */
Player::Player(Game* game, double c, double r, int w, int h, const std::wstring& filename, int tileHeight,
               const std::wstring& filename2, double mPA, int mPX, int mPY, bool isChest)
    : Item(game, filename), mGame(game), mLocation(c * tileHeight, (r + 1) * tileHeight - h),
      mTarget(c * tileHeight, (r + 1) * tileHeight - h), mWidth(w), mHeight(h),
      mMouthAngle(0), mTargetAngle(mPA), mMouthPivot(mPX, mPY), mIsChest(isChest)
{
    wxString path = L"images/" + filename;
    if (!mBitmap.LoadFile(path, wxBITMAP_TYPE_ANY))
    {
        std::wcout << L"Failed to load: " << path.ToStdWstring() << std::endl;
    }

    wxString path2 = L"images/" + filename2;
    if (!mSecondaryBitmap.LoadFile(path2, wxBITMAP_TYPE_ANY))
    {
        std::wcout << L"Failed to load: " << path.ToStdWstring() << std::endl;
    }
}

/**
 * Draw the player
 * @param gc The graphics context to draw on
 */
void Player::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (mIsChest)
    {
        if (mBitmap.IsOk())
        {
            gc->DrawBitmap(mBitmap, mLocation.m_x, mLocation.m_y, mWidth, mHeight);
        }

        if (mSecondaryBitmap.IsOk())
        {
            gc->PushState();

            gc->Translate(mLocation.m_x + mMouthPivot.x + mWidth * 0.1, mLocation.m_y + mMouthPivot.y + mHeight * 0.3);

            gc->Rotate(mMouthAngle);

            gc->DrawBitmap(mSecondaryBitmap, -mMouthPivot.x-mWidth * 0.1, -mMouthPivot.y-mHeight * 0.3, mWidth, mHeight - (mHeight * 0.7));

            gc->PopState();
        }
    }
    else
    {
        if (mBitmap.IsOk())
        {
            gc->DrawBitmap(mBitmap, mLocation.m_x, mLocation.m_y, mWidth, mHeight);
        }

        if (mSecondaryBitmap.IsOk())
        {
            gc->PushState();

            gc->Translate(mLocation.m_x + mMouthPivot.x + mWidth * 0.1, mLocation.m_y + mMouthPivot.y + mHeight * 0.3);

            gc->Rotate(mMouthAngle);

            gc->DrawBitmap(mSecondaryBitmap, -mMouthPivot.x-mWidth * 0.1, -mMouthPivot.y-mHeight * 0.3, mWidth, mHeight * 0.7);

            gc->PopState();
        }
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Player::Update(double elapsed)
{
    auto d = mTarget - mLocation;
    auto distance = d.GetVectorLength();
    auto step = MaxSpeed * elapsed;

    if (distance > step)
    {
        d.Normalize();
        mLocation += d * step;
    }
    else
    {
        mLocation = mTarget;
    }

    if (!mAnimating) return;

    double speed = mIsChest ? 3.0 : 6.0;
    double maxAngle = mIsChest ? 1.2 : mTargetAngle;

    if (mOpening) {
        mMouthAngle += speed * elapsed;
        if (mMouthAngle >= mTargetAngle) {
            mMouthAngle = mTargetAngle;
            mOpening = false;
        }
    } else {
        mMouthAngle -= speed * elapsed;
        if (mMouthAngle <= 0) {
            mMouthAngle = 0;
            mAnimating = false;
        }
    }
}

/**
 * Sets the players location after left-down mouse click
 * @param x
 * @param y
 */
void Player::SetPlayerLocation(int x, int y)
{
    if (!mGame)
    {
        return;
    }

    auto hitItem = mGame->HitTest(x, y);
    if (hitItem && hitItem->IsLetter())
    {
    }

    mTarget = wxPoint2DDouble(x, y);
}

/**
 * function to start the opening
 */
void Player::StartOpening() {
    if (!mAnimating) {
        mAnimating = true;
        mOpening = true;
    }
}