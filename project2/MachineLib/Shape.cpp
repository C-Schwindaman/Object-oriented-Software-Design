/**
 * @file Shape.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Shape.h"
#include "Pulley.h"

/**
 * Constructor
 */
Shape::Shape()
{
    mSink.SetComponent(this);
}

/**
 * Set the rotation for this shape
 * @param rotation New rotation amount
 */
void Shape::SetRotation(double rotation)
{
    Component::SetRotation(rotation);
}

/**
 * Set the position for the root of the motor
 * @param x x position to place the motor
 * @param y y position to place the motor
 */
void Shape::SetPosition(int x, int y)
{
    SetLocation(wxPoint(x, y));
    mPosition = wxPoint(x, y);
}

/**
 * Set the position for the root of the pulley
 * @param pulley The bottom pulley position
 */
void Shape::SetPosition(std::shared_ptr<Pulley> pulley)
{
    SetLocation(pulley->GetPosition());
    mPosition = pulley->GetPosition();
}