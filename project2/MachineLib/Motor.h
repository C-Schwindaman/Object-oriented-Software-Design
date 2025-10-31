/**
 * @file Motor.h
 * @author Cameron Schwindaman
 *
 * A class that represents a motor component
 */
 
#ifndef MOTOR_H
#define MOTOR_H

#include "Component.h"
#include "RotationSource.h"

/**
 * A class that represents a motor component
 */
class Motor : public Component {
private:
    /// The resources directory
    std::wstring mResourcesDir;

    /// The body of the motor
    Polygon mBody;

    /// Position x,y in pixels as a point
    wxPoint mPosition = wxPoint(0, 0);

    /// The rotation time of the motor
    double mRotation = 0;

    /// The speed of the motor
    double mSpeed = 0;

    /// Rotation source for this component
    RotationSource mSource;

public:
    /** Copy constructor disabled */
    Motor(const Motor &) = delete;
    /** Assignment operator disabled */
    void operator=(const Motor &) = delete;

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    Motor(std::wstring resourcesDir);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPosition(int x, int y);
    void SetTime(double time);
    void SetSpeed(double speed);
    void SetRotation(double rotation) override;
};

#endif //MOTOR_H