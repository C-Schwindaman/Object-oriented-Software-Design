/**
 * @file PolyDrawable.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 */
PolyDrawable::PolyDrawable(const std::wstring &name) : Drawable(name)
{
}

/**
 * Draw this drawable
 * @param graphics Graphics object to draw on
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }
}

/**
 * Test to see if we have been clicked on by the mouse
 * @param pos Position to test
 * @return true if clicked on
 */
bool PolyDrawable::HitTest(wxPoint pos)
{
    return mPath.Contains(pos.x, pos.y);
}

/**
 * Add a point to this drawable
 * @param point The point to add
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}
