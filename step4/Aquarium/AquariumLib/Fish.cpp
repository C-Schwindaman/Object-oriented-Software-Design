/**
 * @file Fish.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <random>
#include "Fish.h"
#include "Aquarium.h"

/// Maximum speed in pixels per second
const double MaxSpeed = 50;

/// Minimum speed in pixels per second
const double MinSpeed = 20;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
    std::uniform_real_distribution<> distribution(MinSpeed, MaxSpeed);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = distribution(aquarium->GetRandom());
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);

    if (mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - 10 - this->GetWidth() / 2) {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    } else if (mSpeedX < 0 && GetX() <= 10 + this->GetWidth() / 2) {
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }

    if (mSpeedY > 0 && GetY() >= GetAquarium()->GetHeight() - 10 - this->GetHeight() / 2) {
        mSpeedY = -mSpeedY;
    } else if (mSpeedY < 0 && GetY() <= 10 + this->GetHeight() / 2) {
        mSpeedY = -mSpeedY;
    }
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the fish into
 */
wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    auto fishNode = Item::XmlSave(node);

    fishNode->AddAttribute(L"speedx", wxString::FromDouble(mSpeedX));
    fishNode->AddAttribute(L"speedy", wxString::FromDouble(mSpeedY));

    return fishNode;
}

/**
 * Load the attributes for a fish node.
 *
 * This is the base class version that loads the attributes
 * common to all fish. Override this to load custom attributes
 * for specific fish.
 *
 * @param node The Xml node we are loading the fish from
 */
void Fish::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"speedx", L"0").ToDouble(&mSpeedX);
    node->GetAttribute(L"speedy", L"0").ToDouble(&mSpeedY);

    if (mSpeedX < 0)
    {
        SetMirror(true);
    }
}

/**
 * Set the speed of the fish in X direction
 * @param speed speed in pixels per second
 */
void Fish::SetSpeedX(double speed)
{
    mSpeedX = speed;
}

/**
 * Set the speed of the fish in Y direction
 * @param speed speed in pixels per second
 */
void Fish::SetSpeedY(double speed)
{
    mSpeedY = speed;
}