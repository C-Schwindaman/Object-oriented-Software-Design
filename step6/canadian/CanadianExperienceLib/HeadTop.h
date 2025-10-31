/**
 * @file HeadTop.h
 * @author Cameron Schwindaman
 *
 * An image drawable for the top of the head.
 */
 
#ifndef HEADTOP_H
#define HEADTOP_H

#include "ImageDrawable.h"

/**
 * An image drawable for the top of the head.
 */
class HeadTop : public ImageDrawable {
private:
    /// Right eye position
    wxPoint mRightEye = wxPoint(0, 0);

    /// Left eye position
    wxPoint mLeftEye = wxPoint(0, 0);

    /// Right eyebrow start position
    wxPoint mStartRightEyebrow = wxPoint(0, 0);

    /// Left eyebrow start position
    wxPoint mStartLeftEyebrow = wxPoint(0, 0);

    /// Right eyebrow end position
    wxPoint mEndRightEyebrow = wxPoint(0, 0);

    /// Left eyebrow end position
    wxPoint mEndLeftEyebrow = wxPoint(0, 0);

public:
    /// Default Constructor (Disabled)
    HeadTop() = delete;
    /// Copy Constructor (Disabled)
    HeadTop(const HeadTop &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const HeadTop &) = delete;

    /**
     * Set the right eye position
     * @param pos The new position
     */
    void SetRightEye(wxPoint pos) { mRightEye = pos; }

    /**
     * Set the left eye position
     * @param pos The new position
     */
    void SetLeftEye(wxPoint pos) { mLeftEye = pos; }

    /**
     * Set the right eyebrow start position
     * @param pos The new position
     */
    void SetStartRightEyebrow(wxPoint pos) { mStartRightEyebrow = pos; }

    /**
     * Set the left eyebrow start position
     * @param pos The new position
     */
    void SetStartLeftEyebrow(wxPoint pos) { mStartLeftEyebrow = pos; }

    /**
     * Set the right eyebrow end position
     * @param pos The new position
     */
    void SetEndRightEyebrow(wxPoint pos) { mEndRightEyebrow = pos; }

   /**
     * Set the left eyebrow end position
     * @param pos The new position
     */
   void SetEndLeftEyebrow(wxPoint pos) { mEndLeftEyebrow = pos; }

    /**
     * Is this a movable drawable?
     * @return true if movable
     */
    bool IsMovable() const override { return true; }

    HeadTop(const std::wstring& name, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    wxPoint TransformPoint(wxPoint p);
    void DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p);
    void DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1, wxPoint p2);
};



#endif //HEADTOP_H
