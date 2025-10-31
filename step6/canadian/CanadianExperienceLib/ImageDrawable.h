/**
 * @file ImageDrawable.h
 * @author Cameron Schwindaman
 *
 * A drawable based on images.
 */
 
#ifndef IMAGEDRAWABLE_H
#define IMAGEDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on images.
 */
class ImageDrawable : public Drawable {
private:
    /// The center of this drawable image
    wxPoint mCenter = wxPoint(0, 0);

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

public:
    /// Default Constructor (Disabled)
    ImageDrawable() = delete;
    /// Copy Constructor (Disabled)
    ImageDrawable(const ImageDrawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const ImageDrawable &) = delete;

    /**
     * Set the center point
     * @param c The new center point
     */
    void SetCenter(wxPoint c) { mCenter = c; }

    /**
     * Get the center point
     * @return The center point
     */
    wxPoint GetCenter() const { return mCenter; }

    ImageDrawable(const std::wstring& name, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    bool HitTest(wxPoint pos);
};

#endif //IMAGEDRAWABLE_H