/**
 * @file Chicken.cpp
 *
 * @author Cameron Schwindaman
 */

#include <iostream>
#include "Chicken.h"

using namespace std;


/**
 * Obtain a chicken description from the user.
 */
void Chicken::ObtainChickenInformation()
{
    cout << endl;
    cout << "Input information about the chicken" << endl;

    // Obtain the ID. This is easy, since it's just a
    // string.
    cout << "Id: ";
    cin >> mId;
}

/**
 * Display the chicken.
 */
void Chicken::DisplayAnimal()
{
    cout << "Chicken: " << mId << endl;
}

/**
 * Checks if a chicken can survive a tornado.
 * @return One for if they survive, zero if not
 */
int Chicken::CanAnimalSurviveTornado()
{
    return 1;
}