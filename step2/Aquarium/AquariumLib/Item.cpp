/**
 * @file Item.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 */
Item::Item(Aquarium *aquarium) : mAquarium(aquarium)
{
}