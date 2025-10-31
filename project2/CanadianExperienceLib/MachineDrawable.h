/**
 * @file MachineDrawable.h
 * @author Cameron Schwindaman
 *
 * A drawable that displays a machine
 */
 
#ifndef MACHINEDRAWABLE_H
#define MACHINEDRAWABLE_H

#include <machine-api.h>
#include "Drawable.h"

/**
 * A drawable that displays a machine
 */
class MachineDrawable : public Drawable {
private:
    /// The machine system to draw
    std::shared_ptr<IMachineSystem> mMachine;

    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// The start frame for the animation
    int mStartFrame = 0;

    /// The current frame from the timeline
    int mCurrentFrame = 0;

public:
    /** Copy constructor disabled */
    MachineDrawable(const MachineDrawable &) = delete;
    /** Assignment operator disabled */
    void operator=(const MachineDrawable &) = delete;

    MachineDrawable(const std::wstring& resourcesDir, int machineNumber);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void OpenDialogBox(wxWindow* parent);
    bool HitTest(wxPoint pos) override;
    void SetStartTimeDialog(wxWindow* parent);
};

#endif //MACHINEDRAWABLE_H