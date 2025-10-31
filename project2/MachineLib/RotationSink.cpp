/**
 * @file RotationSink.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "RotationSink.h"
#include "Component.h"

/**
 * Set the component rotation for this sink
 * @param rotation New rotation amount
 */
void RotationSink::Rotate(double rotation)
{
    mComponent->SetRotation(rotation);
}