/**
 * @file Machine.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"

/**
 * Add a component to this machine.
 * @param component The component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

/**
 * Draw the machine
 * @param graphics Graphics object to render to
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Compute how many frames we have moved
 * @param delta The time that has passed
 */
void Machine::Advance(double delta)
{
    for (auto component : mComponents)
    {
        component->Advance(delta);
    }
}