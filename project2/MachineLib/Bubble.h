/**
 * @file Bubble.h
 * @author Cameron Schwindaman
 *
 * A class that represents a bubble
 */
 
#ifndef BUBBLE_H
#define BUBBLE_H

#include "BubbleBlower.h"
#include "Component.h"

/**
 * A class that represents a bubble
 */
class Bubble : public Component {
private:
    /// The resources directory
    std::wstring mResourcesDir;

    /// The position of the bubble
    wxPoint2DDouble mPosition = wxPoint2DDouble(0, 0);

    /// The velocity of the bubble
    wxPoint2DDouble mVelocity = wxPoint2DDouble(0, 0);

    /// The bubble blower this bubble is a part of
    BubbleBlower* mBubbleBlower;

    /// Current radius of the bubble
    int mRadius;

public:
    /** Copy constructor disabled */
    Bubble(const Bubble &) = delete;
    /** Assignment operator disabled */
    void operator=(const Bubble &) = delete;

    /**
     * Get the position of the bubble
     * @return Position of the bubble
     */
    wxPoint2DDouble GetPosition() { return mPosition; }

    /**
     * Set the bubble blower this bubble is a part of
     * @param blower New bubble blower this bubble is a part of
     */
    void SetBubbleBlower(BubbleBlower* blower) { mBubbleBlower = blower; }

    Bubble(std::wstring resourcesDir, wxPoint2DDouble position, wxPoint2DDouble velocity);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool TryExpand(std::mt19937& rng);
};

#endif //BUBBLE_H