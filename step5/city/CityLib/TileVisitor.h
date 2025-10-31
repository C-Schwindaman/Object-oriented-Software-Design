/**
 * @file TileVisitor.h
 *
 * @author Anik Momtaz
 * @author Charles B. Owen
 *
 * Tile visitor base class.
 */

#ifndef CITY_TILEVISITOR_H
#define CITY_TILEVISITOR_H

// Forward references to all tile types
class TileBuilding;
class TileLandscape;
class TileGarden;
class TileWater;
class TileFirehouse;

/**
 * Tile visitor base class
 */
class TileVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    TileVisitor() {}

public:
    virtual ~TileVisitor() {}

    /**
     * Visit a TileBuilding object
     * @param building Building we are visiting
     */
    virtual void VisitBuilding(TileBuilding* building) {}

    /**
     * Visit a TileLandscape object
     * @param landscape Landscape tile we are visiting
     */
    virtual void VisitLandscape(TileLandscape* landscape) {}

    /**
     * Visit a TileGarden object
     * @param garden Garden we are visiting
     */
    virtual void VisitGarden(TileGarden* garden) {}

    /**
     * Visit a water file
     * @param water Tile object we are visiting
     */
    virtual void VisitWater(TileWater* water) {}

    /**
     * Visit a firehouse
     * @param firehouse Tile object we are visiting
     */
    virtual void VisitFirehouse(TileFirehouse* firehouse) {}
};

#endif //CITY_TILEVISITOR_H