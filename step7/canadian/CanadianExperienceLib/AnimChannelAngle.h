/**
 * @file AnimChannelAngle.h
 * @author Cameron Schwindaman
 *
 * Animation channel for angles.
 */
 
#ifndef ANIMCHANNELANGLE_H
#define ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:
    /// The animation channel angle
    double mAngle = 0;

protected:
    /// Class that represents a keyframe angle
    class KeyframeAngle : public Keyframe
    {
    private:
        /// The keyframe angle
        double mAngle;

        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    public:
        /// Default Constructor (Disabled)
        KeyframeAngle() = delete;
        /// Copy Constructor (Disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const KeyframeAngle &) = delete;

        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /**
         * Get the keyframe angle
         * @return Keyframe angle
         */
        double GetAngle() const { return mAngle; }

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyframe 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }
    };

    void Tween(double t);

private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelAngle() {}
    /// Copy Constructor (Disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const AnimChannelAngle &) = delete;

    /** Destructor */
    virtual ~AnimChannelAngle() {}

    /**
     * Get the animation channel angle
     * @return Animation channel angle
     */
    double GetAngle() const { return mAngle; }

    void SetKeyframe(double angle);
};

#endif //ANIMCHANNELANGLE_H