/**
 * @file Machine.h
 * @author Cameron Schwindaman
 *
 * A class that represents a machine
 */
 
#ifndef MACHINE_H
#define MACHINE_H

class Component;
class MachineSystem;

/**
 * A class that represents a machine
 */
class Machine {
private:
    /// Machine number
    int mMachineNumber;

    /// The components in the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The current time
    double mTime = 0;

    /// The system this machine is a part of
    MachineSystem* mSystem;

public:
    /** Copy constructor disabled */
    Machine(const Machine &) = delete;
    /** Assignment operator disabled */
    void operator=(const Machine &) = delete;

    /**
     * Constructor
     * @param machineNumber The machine number to set
     */
    Machine(int machineNumber) : mMachineNumber(machineNumber) {}

    /**
     * Set the current time
     * @param time New current time
     */
    void SetTime(double time) { mTime = time; }

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetTime() { return mTime; }

    /**
     * Set the system this machine is a part of
     * @param system New system this machine is a part of
     */
    void SetMachineSystem(MachineSystem* system) { mSystem = system; }

    /**
     * Get the system this machine is a part of
     * @return System this machine is a part of
     */
    MachineSystem* GetMachineSystem() { return mSystem; }

    void AddComponent(std::shared_ptr<Component> component);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Advance(double delta);
};



#endif //MACHINE_H
