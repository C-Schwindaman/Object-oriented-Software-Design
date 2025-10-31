/**
 * @file SlimedVisitor.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"

#include "SlimedVisitor.h"
#include "TileBuilding.h"

/**
 * Visit a TileBuilding object
 * @param building Building tile we are visiting
 */
void SlimedVisitor::VisitBuilding(TileBuilding* building) {
    if (building->IsSlimed()) {
        mSlimedBuildings++;
    }
}