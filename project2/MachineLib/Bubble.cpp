/**
* @file Bubble.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Bubble.h"
#include "BubbleBlower.h"

/// Gravity in pixels per second
const float Gravity = 2;

/// Bubble as a circle shape with 20 radius
const int BubbleSize = 20;

/// Probability of a bubble expanding
const double BubbleExpansionProbability = 0.05;

/// The maximum possible radius of a bubble, after which it pops
const int BubbleMaximumRadius = 30;

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 * @param position The position of the bubble
 * @param velocity The velocity of the bubble
 */
Bubble::Bubble(std::wstring resourcesDir, wxPoint2DDouble position, wxPoint2DDouble velocity) : mResourcesDir(resourcesDir), mPosition(position), mVelocity(velocity)
{
    auto polygon = new Polygon();
    polygon->Circle(BubbleSize);
    polygon->SetImage(mResourcesDir + L"/bubble.png");
    SetPolygon(polygon);

    mPosition = position;
    mRadius = BubbleSize;
}

/**
 * Draw the bubble
 * @param graphics Graphics object to render to
 */
void Bubble::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto polygon = GetPolygon();
    if (polygon != nullptr)
    {
        polygon->DrawPolygon(graphics, mPosition.m_x, mPosition.m_y);

        auto delta = mBubbleBlower->GetDelta();
        mVelocity = wxPoint2DDouble(mVelocity.m_x, mVelocity.m_y + Gravity * delta);
        mPosition = wxPoint2DDouble(mPosition.m_x + mVelocity.m_x * delta, mPosition.m_y + mVelocity.m_y * delta);
    }
}

/**
 * Try to expand the bubble
 * @param rng Random number generator
 * @return True if the bubble exceeds the maximum
 */
bool Bubble::TryExpand(std::mt19937& rng)
{
    std::uniform_real_distribution<> dist(0.0, 1.0);
    if (dist(rng) < BubbleExpansionProbability)
    {
        mRadius += 1;

        auto polygon = new Polygon();
        polygon->Circle(mRadius);
        polygon->SetImage(mResourcesDir + L"/bubble.png");
        SetPolygon(polygon);
    }

    return mRadius > BubbleMaximumRadius;
}