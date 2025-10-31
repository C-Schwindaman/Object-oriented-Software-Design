/**
 * @file MachineDrawable.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "MachineDrawable.h"

#include "Actor.h"
#include "Timeline.h"

/// The name of the drawable
const std::wstring &name = L"MachineDrawable";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 * @param machineNumber The number of the machine
 */
MachineDrawable::MachineDrawable(const std::wstring& resourcesDir, int machineNumber) : Drawable(name), mResourcesDir(resourcesDir)
{
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();
    mMachine->ChooseMachine(machineNumber);
}

/**
 * Draw the machine
 * @param graphics Graphics object to render to
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.75f;

    mCurrentFrame = GetAngleChannel()->GetTimeline()->GetCurrentFrame();

    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);
    mMachine->SetLocation(wxPoint(0, 0));
    if (mCurrentFrame >= mStartFrame)
    {
        mMachine->SetMachineFrame(mCurrentFrame);
    }
    else
    {
        mMachine->SetMachineFrame(0);
    }
    mMachine->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Open the dialog box to select a machine
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
void MachineDrawable::OpenDialogBox(wxWindow* parent)
{
    MachineDialog dialog(parent, mMachine);
    if (dialog.ShowModal() == wxID_OK)
    {
        SetStartTimeDialog(parent);
    }
}

/**
 * Test to see if we have been clicked on by the mouse
 * @param pos Position to test
 * @return true if clicked on
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    return false;
}

/**
 * Open the dialog box to select the start frame
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
void MachineDrawable::SetStartTimeDialog(wxWindow* parent)
{
    wxTextEntryDialog dlg(parent, L"Enter start frame for this machine:",
                          L"Set Start Time",
                          std::to_wstring(mStartFrame));

    if (dlg.ShowModal() == wxID_OK)
    {
        int frame;
        if (dlg.GetValue().ToInt(&frame))
        {
            mStartFrame = frame;
        }
    }
}