/**
 * @file Cow.h
 *
 * @author Cameron Schwindaman
 *
 * Class that describes a cow.
 */
 
#ifndef STEP1_COW_H
#define STEP1_COW_H

#include <string>
#include "Animal.h"

/**
 * Class that describes a cow.
 */
class Cow : public Animal
{
private:
    /// The types of cow we can have on our farm
    enum class Type {Bull, BeefCow, MilkCow};

    /// The cow's name
    std::string mName;

    /// The type of cow: Bull, BeefCow, or MilkCow
    Type mType =Type::MilkCow;

    /// The milk production for a cow in gallons per day
    double mMilkProduction = 0;

public:
    void ObtainCowInformation();
    void DisplayAnimal();
    int CanAnimalSurviveTornado();
};


#endif //STEP1_COW_H