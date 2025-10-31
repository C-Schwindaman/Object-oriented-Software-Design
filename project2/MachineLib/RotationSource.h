/**
 * @file RotationSource.h
 * @author Cameron Schwindaman
 *
 * A source for a component's rotation
 */
 
#ifndef ROTATIONSOURCE_H
#define ROTATIONSOURCE_H
#include "RotationSink.h"

class Component;
class RotationSink;

/**
 * A source for a component's rotation
 */
class RotationSource {
private:
    /// The components this source is rotating
    Component* mComponent;

    /// The components this source is rotating
    std::vector<RotationSink*> mSinks;

public:
    /** Copy constructor disabled */
    RotationSource(const RotationSource &) = delete;
    /** Assignment operator disabled */
    void operator=(const RotationSource &) = delete;

    /**
     * Constructor
     * @param component The component this source is rotating
     */
    RotationSource(Component* component) : mComponent(component) {}

    void SetRotation(double rotation);
    void AddSink(RotationSink* sink);
};

#endif //ROTATIONSOURCE_H