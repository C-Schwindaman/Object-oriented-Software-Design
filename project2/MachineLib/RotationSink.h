/**
 * @file RotationSink.h
 * @author Cameron Schwindaman
 *
 * A sink for a component's rotation
 */
 
#ifndef ROTATIONSINK_H
#define ROTATIONSINK_H

class Component;

/**
 * A sink for a component's rotation
 */
class RotationSink {
private:
    /// The component this source is rotating
    Component* mComponent = nullptr;

public:
    /** Copy constructor disabled */
    RotationSink(const RotationSink &) = delete;
    /** Assignment operator disabled */
    void operator=(const RotationSink &) = delete;
    void Rotate(double rotation);

    /**
     * Constructor
     */
    RotationSink() {}

    /**
     * Set the component this source is rotating
     * @param component The new component this source is rotating
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this source is rotating
     * @return The component this source is rotating
     */
    Component* GetComponent() { return mComponent; }
};

#endif //ROTATIONSINK_H