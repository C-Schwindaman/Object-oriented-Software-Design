/**
 * @file Pulley.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Pulley.h"

/// Maximum amount to rock the belt
const double BeltRockAmount = 0.01;

/// How quickly to rock the belt in radians per second
/// This is divided by the length to get the actual rate
const double BeltRockBaseRate = M_PI * 1000;

/**
 * Constructor
 * @param radius The radius of the pulley
 */
Pulley::Pulley(int radius) : mSource(this)
{
    Circle(radius);
    mSink.SetComponent(this);
    mRadius = radius;
}

/**
 * Set the position for the root of the pulley
 * @param x x position to place the pulley
 * @param y y position to place the pulley
 */
void Pulley::SetPosition(int x, int y)
{
    SetLocation(wxPoint(x, y));
    mPosition = wxPoint(x, y);
}

/**
 * Set the position for the root of the pulley
 * @param pulley The bottom pulley position
 */
void Pulley::SetPosition(std::shared_ptr<Pulley> pulley)
{
    SetLocation(pulley->GetPosition());
    mPosition = pulley->GetPosition();
}

/**
 * Get the position for the root of the pulley
 * @return x,y position to place the pulley
 */
wxPoint Pulley::GetPosition()
{
    return mPosition;
}

/**
 * Set the pulley that is driven by this pulley
 * @param driven The driven pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> driven)
{
    mBeltConnectedPulley = driven;
}

/**
 * Set the rotation for this component
 * @param rotation Relative number of turns to set.
 */
void Pulley::SetRotation(double rotation)
{
    // Upcall to ensure the polygon rotation gets set
    Component::SetRotation(rotation);

    // Set the rotation for any source
    mSource.SetRotation(rotation);

    if (mBeltConnectedPulley != nullptr)
    {
        // Set the rotation for any pulley we
        // are connected to by a belt.
        mBeltConnectedPulley->SetRotation(rotation * (mRadius/mBeltConnectedPulley->GetRadius()));
    }
}

/**
 * Draw the pulley
 * @param graphics Graphics object to render to
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mBeltConnectedPulley != nullptr)
    {
        // Variables
        auto x1 = mPosition.x;
        auto y1 = mPosition.y;
        auto r1 = mRadius - 3;
        auto x2 = mBeltConnectedPulley->GetPosition().x;
        auto y2 = mBeltConnectedPulley->GetPosition().y;
        auto r2 = mBeltConnectedPulley->GetRadius() - 3;

        // Trigonometry calculations
        auto theta = atan2(y2-y1, x2-x1);
        auto phi = asin((r2-r1)/sqrt(pow(x2-x1, 2)+pow(y2-y1, 2)));
        auto beta1 = theta + phi + M_PI / 2;
        auto beta2 = theta - phi - M_PI / 2;

        // Endpoints
        auto p1 = wxPoint(x1+(r1*cos(beta1)), y1+(r1*sin(beta1)));
        auto p2 = wxPoint(x2+(r2*cos(beta1)), y2+(r2*sin(beta1)));
        auto p3 = wxPoint(x1+(r1*cos(beta2)), y1+(r1*sin(beta2)));
        auto p4 = wxPoint(x2+(r2*cos(beta2)), y2+(r2*sin(beta2)));

        wxPen pen(*wxBLACK, 2);
        graphics->SetPen(pen);

        if (mFlappingBelts)
        {
            // Belt midpoint vectors
            wxPoint2DDouble mid1 = (wxPoint2DDouble(p1) + wxPoint2DDouble(p2)) / 2.0;
            wxPoint2DDouble mid2 = (wxPoint2DDouble(p3) + wxPoint2DDouble(p4)) / 2.0;

            // Perpendicular vector (normal to belt direction)
            wxPoint2DDouble dir1 = p2 - p1;
            wxPoint2DDouble normal1(-dir1.m_y, dir1.m_x);  // 90-degree rotation
            normal1.Normalize();

            wxPoint2DDouble dir2 = p4 - p3;
            wxPoint2DDouble normal2(-dir2.m_y, dir2.m_x);
            normal2.Normalize();

            // Length of belt segments
            double len1 = hypot(p2.x - p1.x, p2.y - p1.y);
            double len2 = hypot(p4.x - p3.x, p4.y - p3.y);

            // Time-based flap amount
            double t = GetCurrentTime(); // Assumes this exists
            double flap1 = sin(BeltRockBaseRate * t / len1) * len1 * BeltRockAmount;
            double flap2 = sin(BeltRockBaseRate * t / len2) * len2 * BeltRockAmount;

            // Control points
            wxPoint2DDouble ctrl1 = mid1 + normal1 * flap1;
            wxPoint2DDouble ctrl2 = mid2 + normal2 * flap2;

            // Draw belt paths
            wxGraphicsPath path1 = graphics->CreatePath();
            path1.MoveToPoint(p1);
            path1.AddCurveToPoint(ctrl1, ctrl1, p2);  // Bezier from p1 -> ctrl1 -> p2
            graphics->StrokePath(path1);

            wxGraphicsPath path2 = graphics->CreatePath();
            path2.MoveToPoint(p3);
            path2.AddCurveToPoint(ctrl2, ctrl2, p4);  // Bezier from p3 -> ctrl2 -> p4
            graphics->StrokePath(path2);
        }
        else
        {
            // Draw belts
            graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
            graphics->StrokeLine(p3.x, p3.y, p4.x, p4.y);
        }
    }
    Component::Draw(graphics);
}