/**
 * @file BuildingCounter.h
 * @author Cameron Schwindaman
 *
 * A visitor for counting buildings
 */
 
#ifndef CITY_BUILDINGCOUNTER_H
#define CITY_BUILDINGCOUNTER_H

#include "TileVisitor.h"

/**
 * A visitor for counting buildings
 */
class BuildingCounter : public TileVisitor {
private:
    /// Buildings counter
    int mNumBuildings = 0;

public:
    void VisitBuilding(TileBuilding* building) override;

    /**
     * Get the number of buildings
     * @return Number of buildings
     */
    int GetNumBuildings() const { return mNumBuildings; }
};

#endif //CITY_BUILDINGCOUNTER_H