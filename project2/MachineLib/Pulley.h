/**
 * @file Pulley.h
 * @author Cameron Schwindaman
 *
 * A class that represents a pulley component
 */
 
#ifndef PULLEY_H
#define PULLEY_H

#include "Component.h"
#include "RotationSink.h"
#include "RotationSource.h"

/**
 * A class that represents a pulley component
 */
class Pulley : public Component {
private:
    /// Rotation source for this component
    RotationSource mSource;

    /// Rotation sink for this component
    RotationSink mSink;

    /// The pulley that is driven by this pulley
    std::shared_ptr<Pulley> mBeltConnectedPulley = nullptr;

    /// Position x,y in pixels as a point
    wxPoint mPosition = wxPoint(0, 0);

    /// The radius of the pulley
    double mRadius;

    /// Are the belts flapping?
    bool mFlappingBelts = false;

public:
    /** Copy constructor disabled */
    Pulley(const Pulley &) = delete;
    /** Assignment operator disabled */
    void operator=(const Pulley &) = delete;

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    /**
     * Get a pointer to the sink object
     * @return Pointer to RotationSink object
     */
    RotationSink *GetSink() { return &mSink; }

    /**
     * Get the radius of the pulley
     * @return Radius of the pulley
     */
    double GetRadius() { return mRadius; }

    /**
     * Set if the belts are flapping
     * @param flapping Are the belts flapping?
     */
    void SetFlappingBelts(bool flapping) { mFlappingBelts = flapping; }

    Pulley(int radius);
    void SetPosition(int x, int y);
    void SetPosition(std::shared_ptr<Pulley> pulley);
    wxPoint GetPosition();
    void Drive(std::shared_ptr<Pulley> driven);
    void SetRotation(double rotation) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //PULLEY_H