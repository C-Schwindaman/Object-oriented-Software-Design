/**
 * @file Shape.h
 * @author Cameron Schwindaman
 *
 * A class that represents a shape component
 */
 
#ifndef SHAPE_H
#define SHAPE_H

#include "Component.h"
#include "Pulley.h"
#include "RotationSink.h"

/**
 * A class that represents a shape component
 */
class Shape : public Component {
private:
    /// Rotation sink for this component
    RotationSink mSink;

    /// Position x,y in pixels as a point
    wxPoint mPosition = wxPoint(0, 0);

public:
    /** Copy constructor disabled */
    Shape(const Shape &) = delete;
    /** Assignment operator disabled */
    void operator=(const Shape &) = delete;

    /**
     * Get a pointer to the sink object
     * @return Pointer to RotationSink object
     */
    RotationSink *GetSink() { return &mSink; }

    /**
     * Get the position y in pixels
     * @return The position y in pixels
     */
    int GetY() { return mPosition.y; }

    Shape();
    void SetRotation(double rotation) override;
    void SetPosition(int x, int y);
    void SetPosition(std::shared_ptr<Pulley> pulley);
};



#endif //SHAPE_H
