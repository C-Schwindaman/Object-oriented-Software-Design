/**
 * @file BuildingCounter.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"

#include "BuildingCounter.h"

/**
 * Visit a TileBuilding object
 * @param building Building we are visiting
 */
void BuildingCounter::VisitBuilding(TileBuilding* building)
{
    mNumBuildings++;
}