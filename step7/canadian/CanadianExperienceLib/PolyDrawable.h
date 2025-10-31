/**
 * @file PolyDrawable.h
 * @author Cameron Schwindaman
 *
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
 
#ifndef POLYDRAWABLE_H
#define POLYDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on polygon images.
 */
class PolyDrawable : public Drawable {
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// The array of point objects
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;

public:
    /// Default Constructor (Disabled)
    PolyDrawable() = delete;
    /// Copy Constructor (Disabled)
    PolyDrawable(const PolyDrawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PolyDrawable &) = delete;

    /**
     * Set the polygon color
     * @param c The new polygon color
     */
    void SetColor(wxColour c) { mColor = c; }

    /**
     * Get the polygon color
     * @return The polygon color
     */
    wxColour GetColor() const { return mColor; }

    PolyDrawable(const std::wstring &name);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;
    void AddPoint(wxPoint point);
};

#endif //POLYDRAWABLE_H