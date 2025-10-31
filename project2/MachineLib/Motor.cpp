/**
 * @file Motor.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Motor.h"
#include "Machine.h"

/// Motors are all 80 pixels square
const int MotorSize = 80;

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Motor::Motor(std::wstring resourcesDir) : mResourcesDir(resourcesDir), mSource(this)
{
    auto polygon = new Polygon();
    polygon->SetImage(mResourcesDir + L"/shaft.png");
    polygon->Rectangle(-MotorSize/2, MotorSize/2, MotorSize, MotorSize);
    SetPolygon(polygon);

    mBody.SetImage(mResourcesDir + L"/motor3.png");
    mBody.Rectangle(-MotorSize/2, MotorSize/2, MotorSize, MotorSize);
}

/**
 * Draw the motor
 * @param graphics Graphics object to render to
 */
void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto polygon = GetPolygon();
    if (polygon != nullptr)
    {
        polygon->DrawPolygon(graphics, mPosition.x, mPosition.y);
    }

    mBody.DrawPolygon(graphics, mPosition.x, mPosition.y);
    SetTime(GetMachine()->GetTime());
    SetRotation(mRotation);
}

/**
 * Set the position for the root of the motor
 * @param x x position to place the motor
 * @param y y position to place the motor
 */
void Motor::SetPosition(int x, int y)
{
    mPosition = wxPoint(x, y);
    SetLocation(wxPoint(x, y));
}

/**
 * Set the rotation time of the motor
 * @param time New rotation time of the motor
 */
void Motor::SetTime(double time)
{
    if (mSpeed != 0) {
        mRotation = mSpeed * time;
    } else {
        mRotation = time;
    }
}

/**
 * Set the speed of the motor
 * @param speed New speed of the motor
 */
void Motor::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 * Set the rotation source for this component
 * @param rotation New rotation amount
 */
void Motor::SetRotation(double rotation)
{
    Component::SetRotation(rotation);

    auto polygon = GetPolygon();
    polygon->SetRotation(rotation);
    SetPolygon(polygon);

    mSource.SetRotation(rotation);
}