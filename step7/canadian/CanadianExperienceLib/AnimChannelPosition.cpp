/**
 * @file AnimChannelPosition.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "AnimChannelPosition.h"

/**
 * Compute a position that is an interpolation
 * between two keyframes
 *
 * This function is called after Use1 and Use2,
 * so we have pointers to valid keyframes of the
 * type KeyframePosition. This function computes the
 * tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelPosition::Tween(double t)
{
    wxPoint a = mKeyframe1->GetPosition();
    wxPoint b = mKeyframe2->GetPosition();

    mPosition = wxPoint(int(a.x + t * (b.x - a.x)),
                        int(a.y + t * (b.y - a.y)));
}

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param position Position for the keyframe.
 */
void AnimChannelPosition::SetKeyframe(wxPoint position)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the position
    auto keyframe = std::make_shared<KeyframePosition>(this, position);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}
