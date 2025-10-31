/**
 * @file Farm.cpp
 *
 * @author Cameron Schwindaman
 */
 
#include "Farm.h"

/** Add an animal to the farm inventory.
 *
 * @param animal An animal to add to the inventory
 */
void Farm::AddAnimal(Animal *animal)
{
    mInventory.push_back(animal);
}

/**
 * Display the farm inventory.
 */
void Farm::DisplayInventory()
{
    for (auto animal : mInventory)
    {
        animal->DisplayAnimal();
    }
}

/**
 * Checks if a farm inventory can survive a tornado.
 * @return Amount of animals that can survive a tornado.
 */
int Farm::CanInventorySurviveTornado()
{
    int surviveTornado = 0;
    for (auto animal : mInventory)
    {
        surviveTornado += animal->CanAnimalSurviveTornado();
    }
    return surviveTornado;
}

/**
 * Farm destructor
 */
Farm::~Farm()
{
    // Iterate over all of the animals, destroying
    // each one.
    for (auto animal : mInventory)
    {
        delete animal;
    }

    // And clear the list
    mInventory.clear();
}