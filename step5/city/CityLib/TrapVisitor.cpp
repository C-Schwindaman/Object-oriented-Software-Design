/**
 * @file TrapVisitor.cpp
 * @author Cameron Schwindaman
 */


#include "pch.h"

#include "TrapVisitor.h"
#include "TileBuilding.h"


/**
 * Visit a TileBuilding object
 * @param building Building tile we are visiting
 */
void TrapVisitor::VisitBuilding(TileBuilding *building)
{
    if (building->IsSlimed()) {
        building->SetTrapped();
    }
}