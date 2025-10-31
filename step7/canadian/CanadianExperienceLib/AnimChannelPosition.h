/**
 * @file AnimChannelPosition.h
 * @author Cameron Schwindaman
 *
 * Animation channel for positions.
 */
 
#ifndef ANIMCHANNELPOSITION_H
#define ANIMCHANNELPOSITION_H

#include "AnimChannel.h"

/**
 * Animation channel for positions.
 */
class AnimChannelPosition : public AnimChannel {
private:
    /// The animation channel position
    wxPoint mPosition = wxPoint(0, 0);

protected:
    /// Class that represents a keyframe position
    class KeyframePosition : public Keyframe
    {
    private:
        /// The keyframe position
        wxPoint mPosition;

        /// The channel this keyframe is associated with
        AnimChannelPosition *mChannel;

    public:
        /// Default Constructor (Disabled)
        KeyframePosition() = delete;
        /// Copy Constructor (Disabled)
        KeyframePosition(const KeyframePosition &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const KeyframePosition &) = delete;

        /**
         * Constructor
         * @param channel The channel we are for
         * @param position The position for the keyframe
         */
        KeyframePosition(AnimChannelPosition *channel, wxPoint position) :
                Keyframe(channel), mChannel(channel), mPosition(position) {}

        /**
         * Get the keyframe position
         * @return Keyframe position
         */
        wxPoint GetPosition() const { return mPosition; }

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyframe 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the position
        void UseOnly() override { mChannel->mPosition = mPosition; }
    };

    void Tween(double t);

private:
    /// The first position keyframe
    KeyframePosition *mKeyframe1 = nullptr;

    /// The second position keyframe
    KeyframePosition *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelPosition() {}
    /// Copy Constructor (Disabled)
    AnimChannelPosition(const AnimChannelPosition &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const AnimChannelPosition &) = delete;

    /** Destructor */
    virtual ~AnimChannelPosition() {}

    /**
     * Get the animation channel position
     * @return Animation channel position
     */
    wxPoint GetPosition() const { return mPosition; }

    void SetKeyframe(wxPoint position);
};

#endif //ANIMCHANNELPOSITION_H