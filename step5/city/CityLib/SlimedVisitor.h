/**
 * @file SlimedVisitor.h
 * @author Cameron Schwindaman
 *
 * A visitor for counting slimed buildings
 */
 
#ifndef CITY_SLIMEDVISITOR_H
#define CITY_SLIMEDVISITOR_H

#include "TileVisitor.h"

/**
 * A visitor for counting slimed buildings
 */
class SlimedVisitor : public TileVisitor {
private:
    /// Slimed buildings counter
    int mSlimedBuildings = 0;

public:
    void VisitBuilding(TileBuilding* building) override;

    /**
     * Get the number of slimed buildings
     * @return Number of slimed buildings
     */
    int GetSlimedBuildings() { return mSlimedBuildings; }
};

#endif //CITY_SLIMEDVISITOR_H