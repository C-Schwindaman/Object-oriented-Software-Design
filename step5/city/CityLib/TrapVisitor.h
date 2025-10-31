/**
 * @file TrapVisitor.h
 * @author Cameron Schwindaman
 *
 * A visitor for trapping buildings
 */
 
#ifndef TRAPVISITOR_H
#define TRAPVISITOR_H

#include "TileVisitor.h"

/**
 * A visitor for trapping buildings
 */
class TrapVisitor : public TileVisitor {
private:

public:
    void VisitBuilding(TileBuilding* building) override;
};

#endif //TRAPVISITOR_H