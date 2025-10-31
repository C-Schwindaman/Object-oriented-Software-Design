/**
 * @file HeadTop.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name The drawable name
 * @param filename The filename for the image
 */
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename): ImageDrawable(name, filename)
{
}

/**
 * Draw the top of the head
 * @param graphics Graphics context to draw on
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);

    DrawEye(graphics, TransformPoint(mLeftEye));
    DrawEye(graphics, TransformPoint(mRightEye));
    DrawEyebrow(graphics, TransformPoint(mStartLeftEyebrow), TransformPoint(mEndLeftEyebrow));
    DrawEyebrow(graphics, TransformPoint(mStartRightEyebrow), TransformPoint(mEndRightEyebrow));
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Draw an eye on the head
 * @param graphics Graphics context to draw on
 * @param p Center point to draw the eye
 */
void HeadTop::DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p)
{
    wxBrush brush(wxColour(0, 0, 0));

    float wid = 15.0f;
    float hit = 20.0f;

    graphics->SetBrush(brush);
    graphics->PushState();
    graphics->Translate(p.x, p.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/**
 * Draw an eyebrow on the head
 * @param graphics Graphics context to draw on
 * @param p1 Starting point to draw the eyebrow
 * @param p2 Ending point to draw the eyebrow
 */
void HeadTop::DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1, wxPoint p2)
{
    wxPen pen(*wxBLACK, 2);

    graphics->SetPen(pen);
    graphics->PushState();
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
    graphics->PopState();
}

/**
 * Add the channels for the top of the head to a timeline
 * @param timeline The timeline class.
 */
void HeadTop::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    timeline->AddChannel(&mPositionChannel);
}

/**
 * Set a keyframe based on the current position.
 */
void HeadTop::SetKeyframe()
{
    Drawable::SetKeyframe();
    mPositionChannel.SetKeyframe(GetPosition());
}

/**
 * Get a keyframe update from the animation system.
 */
void HeadTop::GetKeyframe()
{
    Drawable::GetKeyframe();
    if (mPositionChannel.IsValid())
    {
        SetPosition(mPositionChannel.GetPosition());
    }
}

/**
 * Deletes a keyframe based on the current position.
 */
void HeadTop::DeleteKeyframe()
{
    Drawable::DeleteKeyframe();
    mPositionChannel.DeleteKeyframe();
}