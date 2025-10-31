/**
 * @file BuildingVisitor.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"

#include "BuildingVisitor.h"
#include "TileBuilding.h"
#include "TileFirehouse.h"

/**
 * Visit a TileBuilding object
 * @param building Building tile we are visiting
 */
void BuildingVisitor::VisitBuilding(TileBuilding *building)
{
    if (building->IsNormal()) {
        building->SetSlimed();
    } else if (building->IsTrapped()) {
        building->Reset();
    }
}

/**
 * Visit a TileFirehouse object
 * @param firehouse Firehouse tile we are visiting
 */
void BuildingVisitor::VisitFirehouse(TileFirehouse* firehouse)
{
    firehouse->SetOpening();
}
