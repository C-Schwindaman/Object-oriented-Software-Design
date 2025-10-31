/**
 * @file Timeline.h
 * @author Cameron Schwindaman
 *
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
 
#ifndef TIMELINE_H
#define TIMELINE_H

class AnimChannel;

/**
 * This class implements a timeline that manages the animation
 */
class Timeline {
private:
    /// How many frames are in the animation
    int mNumFrames = 300;

    /// The number of frames per second
    int mFrameRate = 30;

    /// The current time in the animation
    double mCurrentTime = 0;

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;

public:
    /// Copy Constructor (Disabled)
    Timeline(const Timeline &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Timeline &) = delete;

    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return mNumFrames / (double)mFrameRate; }

    /** Get the current frame.
     *
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return mCurrentTime * mFrameRate; }

    Timeline();
    void AddChannel(AnimChannel *channel);
    void SetCurrentTime(double t);
};

#endif //TIMELINE_H