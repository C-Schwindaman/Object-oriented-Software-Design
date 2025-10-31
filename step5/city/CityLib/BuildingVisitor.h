/**
 * @file BuildingVisitor.h
 * @author Cameron Schwindaman
 *
 * A visitor for buildings
 */
 
#ifndef CITY_BUILDINGVISITOR_H
#define CITY_BUILDINGVISITOR_H

#include "TileVisitor.h"

/**
 * A visitor for buildings
 */
class BuildingVisitor : public TileVisitor {
private:

public:
    void VisitBuilding(TileBuilding* building) override;
    void VisitFirehouse(TileFirehouse* firehouse) override;
};

#endif //CITY_BUILDINGVISITOR_H