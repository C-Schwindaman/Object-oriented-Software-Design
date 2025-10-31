/**
 * @file Actor.h
 * @author Cameron Schwindaman
 *
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
 
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <memory>
#include <vector>
#include "AnimChannelPosition.h"

class Drawable;
class Picture;

/**
 * Class for actors in our drawings.
 */
class Actor {
private:
    /// The actor name
    std::wstring mName;

    /// Is this actor enabled (drawable)?
    bool mEnabled = true;

    /// The actor position
    wxPoint mPosition = wxPoint(0, 0);

    /// Is this actor mouse clickable?
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The picture this actor is in
    Picture* mPicture = nullptr;

    /// The animation channel for animating the position of this actor
    AnimChannelPosition mPositionChannel;

public:
    /// Default Constructor (Disabled)
    Actor() = delete;
    /// Copy Constructor (Disabled)
    Actor(const Actor &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Actor &) = delete;

    /**
     * Get the actor name
     * @return Actor name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * The actor position
     * @return The actor position as a point
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @param pos The new actor position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /**
     * The picture the actor is in
     * @return Picture the actor is in
     */
    Picture* GetPicture() const { return mPicture; }

    /**
     * The animation position channel the actor is in
     * @return Animation position channel the actor is in
     */
    AnimChannelPosition *GetPositionChannel() { return &mPositionChannel; }

    virtual ~Actor();
    Actor(const std::wstring &name);
    void SetRoot(std::shared_ptr<Drawable> root);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    std::shared_ptr<Drawable> HitTest(wxPoint pos);
    void AddDrawable(std::shared_ptr<Drawable> drawable);
    void SetPicture(Picture* picture);
    void SetKeyframe();
    void GetKeyframe();
    void DeleteKeyframe();
};

#endif //ACTOR_H