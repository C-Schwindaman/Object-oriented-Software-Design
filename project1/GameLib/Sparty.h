/**
 * @file Sparty.h
 * @author Cameron Schwindaman
 *
 * A class for the Sparty player
 */
 
#ifndef SPARTY_H
#define SPARTY_H

#include "Game.h"
#include "Player.h"

/**
 * A class for the Sparty player
 */
class Sparty : public Player
{
private:

public:
    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty &) = delete;

    /// Assignment operator
    void operator=(const Sparty &) = delete;

    Sparty(Game* game, double c, double r, int w, int h, const std::wstring& filename, int tileHeight,
       const std::wstring& filename2, double mPA, int mPX, int mPY);

    void Accept(Visitor* visitor) override;
};

#endif //SPARTY_H