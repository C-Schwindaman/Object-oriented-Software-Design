/**
 * @file TileFirehouse.h
 *
 * @author Anik Momtaz
 *
 * Class that implements a firehouse tile
 */

#ifndef CITY_TILEFIREHOUSE_H
#define CITY_TILEFIREHOUSE_H

#include "Tile.h"
#include "City.h"

/**
 * Class that implements a firehouse tile
 */
class TileFirehouse : public Tile {
private:
    /// The firehouse state possibilities
    enum class State {Idle, Opening, DispatchedOne, DispatchedTwo};

    /// The current firehouse state
    State mState = State::Idle;

    /// The duration for the current firehouse image
    double mFirehouseImageDuration = 0;

    /// The city the tile is stored in
    City* mCity;

public:
    TileFirehouse(City *city);

    /// Default constructor (disabled)
    TileFirehouse() = delete;

    /// Copy constructor (disabled)
    TileFirehouse(const TileFirehouse &) = delete;

    /// Assignment operator
    void operator=(const TileFirehouse &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;
    void SetOpening();

    void Update(double elapsed) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitFirehouse(this); }
};

#endif //CITY_TILEFIREHOUSE_H
