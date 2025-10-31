/**
 * @file Drawable.h
 * @author Cameron Schwindaman
 *
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
 
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include <memory>
#include "AnimChannelAngle.h"

class Actor;
class Timeline;

/**
 * Abstract base class for drawable elements of our picture.
 */
class Drawable {
private:
    /// The position of this drawable relative to its parent
    wxPoint mPosition = wxPoint(0, 0);

    /// The drawable name
    std::wstring mName;

    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    Actor *mActor = nullptr;

    /// The parent drawable
    Drawable* mParent = nullptr;

    /// The children drawables
    std::vector<std::shared_ptr<Drawable>> mChildren;

    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannel;

protected:
    /// The actual postion in the drawing
    wxPoint mPlacedPosition = wxPoint(0, 0);

    /// The actual rotation in the drawing
    double mPlacedR = 0;

    Drawable(const std::wstring &name);
    wxPoint RotatePoint(wxPoint point, double angle);

public:
    /// Default Constructor (Disabled)
    Drawable() = delete;
    /// Copy Constructor (Disabled)
    Drawable(const Drawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Drawable &) = delete;

    /**
     * Get the drawable name
     * @return The drawable name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Is this a movable drawable?
     * @return true if movable
     */
    virtual bool IsMovable() const { return false; }

    /**
     * Set the drawable position
     * @param pos The new drawable position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }

    /**
     * Get the drawable position
     * @return The drawable position
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set the rotation angle in radians
     * @param r The new rotation angle in radians
     */
    void SetRotation(double r) { mRotation = r; }

    /**
     * Get the rotation angle in radians
     * @return The rotation angle in radians
     */
    double GetRotation() const { return mRotation; }

    /**
     * Set the parent drawable
     * @param p The new parent drawable
     */
    void SetParent(Drawable* p) { mParent = p; }

    /**
     * Get the parent drawable
     * @return The parent drawable
     */
    Drawable* GetParent() const { return mParent; }

    /**
     * The angle animation channel
     * @return Pointer to animation channel
     */
    AnimChannelAngle *GetAngleChannel() { return &mChannel; }

    virtual ~Drawable();
    void SetActor(Actor* actor);
    void Place(wxPoint offset, double rotation);
    void AddChild(std::shared_ptr<Drawable> child);
    void Move(wxPoint delta);
    virtual void SetTimeline(Timeline* timeline);
    virtual void SetKeyframe();
    virtual void GetKeyframe();
    virtual void DeleteKeyframe();

    /**
     * Draw this drawable
     * @param graphics Graphics object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) = 0;
};

#endif //DRAWABLE_H