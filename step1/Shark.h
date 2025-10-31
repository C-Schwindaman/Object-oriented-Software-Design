/**
 * @file Shark.h
 *
 * @author Cameron Schwindaman
 *
 * Class that describes a shark.
 */
 
#ifndef STEP1_SHARK_H
#define STEP1_SHARK_H

#include <string>
#include "Animal.h"

/**
 * Class that describes a shark.
 */
class Shark : public Animal
{
private:
    /// The types of shark we can have on our farm
    enum class Type {GreatWhite, HammerHead, Land, Nurse, Thresher};

    /// The shark's name
    std::string mName;

    /// The breed of shark: GreatWhite, HammerHead, Land, Nurse, Thresher
    Type mBreed =Type::GreatWhite;

public:
    void ObtainSharkInformation();
    void DisplayAnimal();
    int CanAnimalSurviveTornado();
};


#endif //STEP1_SHARK_H