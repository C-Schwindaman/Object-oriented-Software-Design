/**
 * @file RotationSource.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "RotationSource.h"
#include "Component.h"
#include "RotationSink.h"

/**
 * Add a sink to this source
 * @param sink The sink to add
 */
void RotationSource::AddSink(RotationSink* sink)
{
    mSinks.push_back(sink);
}

/**
 * Set the rotation sink for this source
 * @param rotation New rotation amount
 */
void RotationSource::SetRotation(double rotation)
{
    for (auto sink : mSinks)
    {
        sink->Rotate(rotation);
    }
}