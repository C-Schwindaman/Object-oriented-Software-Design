/**
 * @file MachineSystem.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    SetMachineNumber(1);
}

/**
 * Draw the machine at the currently specified location
 * @param graphics Graphics object to render to
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    // This will put the machine where it is supposed to be drawn
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);

    mMachine->Draw(graphics);

    graphics->PopState();
}

/**
 * Set the machine number
 * @param machine An integer number. Each number makes a different machine
 */
void MachineSystem::ChooseMachine(int machine)
{
    if(machine == 1)
    {
        mMachineNumber = 1;
        SetMachineNumber(1);
    }
    else
    {
        mMachineNumber = 2;
        SetMachineNumber(2);
    }
}

/**
 * Set the machine number, creating the appropriate machine
 * @param machine Machine number
 */
void MachineSystem::SetMachineNumber(int machine)
{
    if(machine == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->SetMachineSystem(this);
    }
    else
    {
        Machine2Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->SetMachineSystem(this);
    }
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        mMachine->SetTime(0);
        mMachineTime = 0;
    }

    while (mFrame < frame) {
        mFrame++;
        mMachine->Advance(1.0 / mFrameRate);
        mMachine->SetTime(mFrame / mFrameRate);
        mMachineTime = mFrame / mFrameRate;
    }
}