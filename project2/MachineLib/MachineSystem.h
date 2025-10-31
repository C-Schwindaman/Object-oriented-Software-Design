/**
 * @file MachineSystem.h
 * @author Cameron Schwindaman
 *
 * A class that represents the machine system
 */
 
#ifndef MACHINESYSTEM_H
#define MACHINESYSTEM_H

#include "IMachineSystem.h"

class Machine;

/**
 * A class that represents the machine system
 */
class MachineSystem : public IMachineSystem {
private:
    /// Location x,y in pixels as a point
    wxPoint mLocation = wxPoint(0, 0);

    /// Current machine animation frame
    int mFrame = 0;

    /// Frame rate in frames per second
    double mFrameRate = 0;

    /// Current machine number
    int mMachineNumber = 1;

    /// Current machine time in seconds
    double mMachineTime = 0;

    /// Flag from the control panel
    int mFlag = 0;

    /// The current machine in the system
    std::shared_ptr<Machine> mMachine;

    /// The resources directory
    std::wstring mResourcesDir;

public:
    /** Copy constructor disabled */
    MachineSystem(const MachineSystem &) = delete;
    /** Assignment operator disabled */
    void operator=(const MachineSystem &) = delete;

    /**
     * Set the position for the root of the machine
     * @param location The x,y location to place the machine
     */
    void SetLocation(wxPoint location) override { mLocation = location; }

    /**
     * Get the location of the machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override { return mLocation; }

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override { mFrameRate = rate; }

    /**
     * Get the expected frame rate in frames per second
     * @return Frame rate in frames per second
     */
    double GetFrameRate() { return mFrameRate; }

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override { return mMachineNumber; }

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override { return mMachineTime; }

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) override { mFlag = flag; }

    MachineSystem(std::wstring resourcesDir);
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void ChooseMachine(int machine) override;
    void SetMachineNumber(int machine);
    void SetMachineFrame(int frame) override;
};

#endif //MACHINESYSTEM_H