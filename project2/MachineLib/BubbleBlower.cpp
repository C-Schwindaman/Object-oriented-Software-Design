/**
 * @file BubbleBlower.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "BubbleBlower.h"
#include "Bubble.h"
#include "Machine.h"

/// Average number of bubbles created per rotation
const double BubblePerRotation = 5;

/// Variance in how many bubbles are created
const double BubbleVariancePerSecond = 100;

/// Range of the random angle bubbles will be blown at
const double BubbleAngleVariance = 0.1;

/// Angle range for the tip of the bubble blower in radians
const double BubbleMachineAngleRange = 0.25;

/// Offset to the tip of bubble blower from middle in pixels
const double BubbleBlowerOffset = 100;

/// Random variance in the bubble blower offset
const double BubbleBlowerOffsetVariance = 5;

/// Minimum bubble velocity
const double BubbleMinimumVelocity = 20;

/// Maximum bubble velocity
const double BubbleMaximumVelocity = 40;

/// Width of the bubble blower in pixels
const int BubbleBlowerWidth = 50;

/// Height of the bubble blower in pixels
const int BubbleBlowerHeight = 150;

/// Y offset to the hilt of the bubble blower in pixels
const int BubbleBlowerHiltOffset = 10;

/// Width of the post in pixels
const int PostWidth = 19;

/// Height of the post in pixels
const int PostHeight = 55;

/// X coordinate of the post in pixels
const int PostXCoordinate = -110;

/// Y coordinate of the post in pixels
const int PostYCoordinate = -376;

/// Bubble has fallen below the bottom of the screen
const int BubbleOffScreen = 200;

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
BubbleBlower::BubbleBlower(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    auto polygon = new Polygon();
    polygon->SetImage(mResourcesDir + L"/blower.png");
    polygon->Rectangle(-BubbleBlowerWidth / 2, BubbleBlowerHiltOffset, BubbleBlowerWidth, BubbleBlowerHeight);
    SetPolygon(polygon);

    mSink.SetComponent(this);

    std::random_device rd;	// Generates a random seed
    mRandom.seed(rd());		// Seed the random number generator
}

/**
 * Set the rotation for this shape
 * @param rotation New rotation amount
 */
void BubbleBlower::SetRotation(double rotation)
{
    Component::SetRotation(rotation);

    if (rotation == 0)
    {
        mBubbles.clear();
        return;
    }

    // Compute how many bubbles to generate for this amount of rotation.
    double newRotation = rotation - mRotation;
    mRotation = rotation;
    auto num = int(newRotation * (BubblePerRotation + Random(-BubbleVariancePerSecond, BubbleVariancePerSecond)));

    for (int i = 0; i < num; i++)
    {
        // GetRotation gets the rotation of the bubble blower.
        // This code computes a vector to the emitting end of the
        // bubble blower. The random value means that position is over
        // the entire end of the machine, not just a single point.
        auto angle = Random(-BubbleAngleVariance, BubbleAngleVariance);
        auto dx = sin(angle);
        auto dy = -cos(angle);

        double angle1;
        if (mBubbleDirection)
        {
            angle1 = angle + Random(-BubbleAngleVariance, BubbleAngleVariance) + M_PI / 2 + M_PI;
        }
        else
        {
            angle1 = angle + Random(-BubbleAngleVariance, BubbleAngleVariance) + M_PI / 2;
        }
        auto dx1 = sin(angle1);
        auto dy1 = -cos(angle1);

        double offset = BubbleBlowerOffset + Random(-BubbleBlowerOffsetVariance, BubbleBlowerOffsetVariance);
        double velocity = Random(BubbleMinimumVelocity, BubbleMaximumVelocity);

        wxPoint2DDouble bubblePosition((float)(mPosition.x+dx * offset), (float)(mPosition.y+dy * offset));
        wxPoint2DDouble bubbleVelocity((float)(dx1 * velocity), (float)(dy1 * velocity));

        auto bubble = std::make_shared<Bubble>(mResourcesDir, bubblePosition, bubbleVelocity);
        mBubbles.push_back(bubble);
        bubble->SetBubbleBlower(this);
    }
}

/**
 * Set the position for the root of the motor
 * @param x x position to place the motor
 * @param y y position to place the motor
 */
void BubbleBlower::SetPosition(int x, int y)
{
    SetLocation(wxPoint(x, y));
    mPosition = wxPoint(x, y);
}

/**
 * Generate a uniform distribution random number from fmValue to toValue
 * @param fmValue Minimum value to generate
 * @param toValue Maximum value to generate
 * @return Random number
 */
double BubbleBlower::Random(double fmValue, double toValue)
{
    std::uniform_real_distribution<> distribution(fmValue, toValue);
    return distribution(mRandom);
}

/**
 * Draw the bubble blower
 * @param graphics Graphics object to render to
 */
void BubbleBlower::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the post
    wxBrush brush(wxColour(0, 0, 0));
    wxPen pen(wxColour(0, 0, 0));
    graphics->SetBrush(brush);
    graphics->SetPen(pen);
    graphics->DrawRectangle(PostXCoordinate, PostYCoordinate, PostWidth, PostHeight);

    auto polygon = GetPolygon();
    if (polygon != nullptr)
    {
        polygon->DrawPolygon(graphics, mPosition.x, mPosition.y);
    }

    for (auto it = mBubbles.begin(); it != mBubbles.end(); )
    {
        auto bubble = *it;
        bubble->Draw(graphics);

        if (mBubbleExpansion)
        {
            if (bubble->GetPosition().m_y > BubbleOffScreen || bubble->TryExpand(mRandom))
            {
                it = mBubbles.erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            if (bubble->GetPosition().m_y > BubbleOffScreen)
            {
                it = mBubbles.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

/**
 * Compute how many frames we have moved
 * @param delta The time that has passed
 */
void BubbleBlower::Advance(double delta)
{
    mDelta = delta;
}