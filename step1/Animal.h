/**
 * @file Animal.h
 *
 * @author Cameron Schwindaman
 *
 * Class that describes an animal
 */
 
#ifndef STEP1_ANIMAL_H
#define STEP1_ANIMAL_H

/**
 * Class that describes an animal.
 */
class Animal
{
private:

public:
    virtual ~Animal();
    /** Display an animal. */
    virtual void DisplayAnimal() {}
    /** Checks if an animal can survive a tornado.
     * @return 0
     */
    virtual int CanAnimalSurviveTornado() {return 0;}
};


#endif //STEP1_ANIMAL_H