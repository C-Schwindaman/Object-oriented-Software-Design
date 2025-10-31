/**
 * @file Shark.cpp
 *
 * @author Cameron Schwindaman
 */

#include <iostream>
#include "Shark.h"

using namespace std;

/**
 * Obtain information from the user about this cow.
 *
 * Asks the user for the information that describes a cow.
 */
void Shark::ObtainSharkInformation() {
    cout << endl;
    cout << "Input information about the shark" << endl;

    // Obtain the name. This is easy, since it's just a
    // string.
    cout << "Name: ";
    cin >> mName;

    // Obtain the breed using a menu. We have a loop so
    // we can handle errors.
    bool valid = false;
    while (!valid)
    {
        cout << "1: Great White" << endl;
        cout << "2: Hammer Head" << endl;
        cout << "3: Land" << endl;
        cout << "4: Nurse" << endl;
        cout << "5: Thresher" << endl;
        cout << "Enter selection and return: ";
        int option;
        cin >> option;
        if (!cin)
        {
            // We have an error. Clear the input and try again
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (option)
        {
        case 1:
            mBreed = Type::GreatWhite;
            valid = true;
            break;

        case 2:
            mBreed = Type::HammerHead;
            valid = true;
            break;

        case 3:
            mBreed = Type::Land;
            valid = true;
            break;

        case 4:
            mBreed = Type::Nurse;
            valid = true;
            break;

        case 5:
            mBreed = Type::Thresher;
            valid = true;
            break;
        }

    }

}

/**
 * Display information about this shark.
 */
void Shark::DisplayAnimal()
{
	cout << "Shark " << mName << " is a ";
	switch (mBreed)
	{
	case Type::GreatWhite:
		cout << "Great White";
		break;

	case Type::HammerHead:
		cout << "Hammer Head";
		break;

	case Type::Land:
		cout << "Land";
	    break;

	case Type::Nurse:
	    cout << "Nurse";
		break;

	case Type::Thresher:
		cout << "Thresher";
		break;
	}
	cout << " Shark" << endl;
}


/**
 * Checks if a shark can survive a tornado.
 * @return One for if they survive, zero if not
 */
int Shark::CanAnimalSurviveTornado()
{
	switch (mBreed)
	{
	case Type::GreatWhite:
		return 1;

	case Type::HammerHead:
		return 1;

	case Type::Land:
		return 0;

	case Type::Nurse:
		return 0;

	case Type::Thresher:
		return 0;
	}
}