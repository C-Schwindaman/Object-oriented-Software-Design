/**
 * @file BubbleBlower.h
 * @author Cameron Schwindaman
 *
 * A class that represents a bubble blower component
 */
 
#ifndef BUBBLEBLOWER_H
#define BUBBLEBLOWER_H

#include <random>
#include "Component.h"
#include "RotationSink.h"

class Bubble;

/// Speed up the bubble animation
const int QuickerBubbles = 3;

/**
 * A class that represents a bubble blower component
 */
class BubbleBlower : public Component {
private:
    /// The resources directory
    std::wstring mResourcesDir;

    /// Rotation sink for this component
    RotationSink mSink;

    /// Random number generator
    std::mt19937 mRandom;

    /// Bubbles generated from blower
    std::list<std::shared_ptr<Bubble>> mBubbles;

    /// The rotation of the bubble blower
    double mRotation = 0;

    /// Position x,y in pixels as a point
    wxPoint mPosition = wxPoint(0, 0);

    /// The time that has passed
    double mDelta = 0;

    /// Are the bubbles going left?
    bool mBubbleDirection = false;

    /// Are the bubbles expanding?
    bool mBubbleExpansion = false;

public:
    /** Copy constructor disabled */
    BubbleBlower(const BubbleBlower &) = delete;
    /** Assignment operator disabled */
    void operator=(const BubbleBlower &) = delete;

    /**
     * Get a pointer to the sink object
     * @return Pointer to RotationSink object
     */
    RotationSink *GetSink() { return &mSink; }

    /**
     * Get the time that has passed
     * @return The time that has passed
     */
    double GetDelta() { return mDelta * QuickerBubbles; }

    /**
     * Set if the bubbles are going to the left
     * @param direction Are the bubbles going left?
     */
    void SetBubbleDirection(bool direction) { mBubbleDirection = direction; }

    /**
     * Set if the bubbles are expanding
     * @param expansion Are the bubbles expanding?
     */
    void SetBubbleDExpansion(bool expansion) { mBubbleExpansion = expansion; }

    /** Iterator that iterates over the bubbles in a bubble blower */
    class BubbleIter
    {
    public:
        /**
         * Constructor
         * @param iter The iterator for our bubble list
         */
        BubbleIter(std::list<std::shared_ptr<Bubble>>::iterator iter) : mIter(iter) {}

        /**
         * Test for end of the iterator
         * @param other Other object to test against
         * @return True if we this position equals not equal to the other position
         */
        bool operator!=(const BubbleIter &other) const
        {
            return mIter != other.mIter;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Bubble> operator *() const
        {
            return *mIter;
        }

        /**
         * Increment the iterator
         * @return Reference to this iterator
         */
        const BubbleIter& operator++()
        {
            ++mIter;
            return *this;
        }

    private:
        /// The iterator for our bubble list
        std::list<std::shared_ptr<Bubble>>::iterator mIter;
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    BubbleIter begin() { return BubbleIter(mBubbles.begin()); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    BubbleIter end() { return BubbleIter(mBubbles.end()); }

    BubbleBlower(std::wstring resourcesDir);
    void SetRotation(double rotation) override;
    void SetPosition(int x, int y);
    double Random(double fmValue, double toValue);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Advance(double delta);
};

#endif //BUBBLEBLOWER_H