/**
 * @file AnimChannel.h
 * @author Cameron Schwindaman
 *
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
 
#ifndef ANIMCHANNEL_H
#define ANIMCHANNEL_H

class Timeline;

/**
 * Base class for animation channels
 */
class AnimChannel {
private:
    /// The animation channel name
    std::wstring mName;

    /// The first keyframe
    int mKeyframe1 = -1;

    /// The second keyframe
    int mKeyframe2 = -1;

    /// The timeline object
    Timeline *mTimeline = nullptr;

protected:
    /// Default constructor
    AnimChannel() {}

    /// Class that represents a keyframe
    class Keyframe
    {
    private:
        /// The keyframe number
        int mFrame;

        /// The channel this keyframe is associated with
        AnimChannel *mChannel;

    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    public:
        /// Default Constructor (Disabled)
        Keyframe() = delete;
        /// Copy Constructor (Disabled)
        Keyframe(const Keyframe &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const Keyframe &) = delete;

        /**
         * Get the keyframe number
         * @return Keyframe number
         */
        int GetFrame() const { return mFrame; }

        /**
         * Set the keyframe number
         * @param frame New keyframe number
         */
        void SetFrame(int frame) { mFrame = frame; }

        /// Use this keyframe as keyframe 1
        virtual void UseAs1() = 0;

        /// Use this keyframe as keyframe 2
        virtual void UseAs2() = 0;

        /// Use this keyframe as the value
        virtual void UseOnly() = 0;
    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Computes the interpolation between two keyframes
     * @param t A t value
     */
    virtual void Tween(double t) = 0;

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:
    /// Copy Constructor (Disabled)
    AnimChannel(const AnimChannel &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const AnimChannel &) = delete;

    /** Destructor */
    virtual ~AnimChannel() {}

    /**
     * Get the animation channel name
     * @return Animation channel name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Set the animation channel name
     * @param name New animation channel name
     */
    void SetName(std::wstring name) { mName = name; }

    /**
     * Get the timeline object
     * @return Timeline object
     */
    Timeline* GetTimeline() const { return mTimeline; }

    /**
     * Set the timeline object
     * @param timeline New timeline object
     */
    void SetTimeline(Timeline* timeline) { mTimeline = timeline; }

    bool IsValid();
    void SetFrame(int currFrame);
    void DeleteKeyframe();
};

#endif //ANIMCHANNEL_H