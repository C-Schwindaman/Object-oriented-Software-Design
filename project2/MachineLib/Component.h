/**
 * @file Component.h
 * @author Cameron Schwindaman
 *
 * A class that represents a component
 */
 
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Polygon.h"

class Machine;

/**
 * A class that represents a component
 */
class Component : public cse335::Polygon
{
private:
    /// Location x,y in pixels as a point
    wxPoint2DDouble mLocation = wxPoint2DDouble(0, 0);

    /// The polygon of the component
    Polygon* mPolygon = nullptr;

    /// Is the polgon set?
    bool mIsPolygon = false;

    /// The machine this component is a part of
    Machine* mMachine;

public:
    /** Copy constructor disabled */
    Component(const Component &) = delete;
    /** Assignment operator disabled */
    void operator=(const Component &) = delete;

    /**
     * Constructor
     */
    Component() {}

    /**
     * Get the polygon of the component
     * @return Polygon of the component
     */
    Polygon* GetPolygon() { return mPolygon; }

    /**
     * Set the location of the component
     * @param location x,y in pixels as a point
     */
    void SetLocation(wxPoint2DDouble location) { mLocation = location; }

    /**
     * Get the machine this component is a part of
     * @return Machine this component is a part of
     */
    Machine* GetMachine() { return mMachine; }

    /**
     * Set the machine this component is a part of
     * @param machine New machine this component is a part of
     */
    void SetMachine(Machine* machine) { mMachine = machine; }

    /**
     * Compute how many frames we have moved
     * @param delta The time that has passed
     */
    virtual void Advance(double delta) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void SetPolygon(Polygon* polygon);
};

#endif //COMPONENT_H