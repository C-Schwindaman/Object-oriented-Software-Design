/**
 * @file Chest.h
 * @author Meghan Carter
 *
 * A class for the Chest player
 */

#ifndef CHEST_H
#define CHEST_H

#include "Game.h"
#include "Player.h"

/**
* Class for a player of type Chest
*/
class Chest : public Player
{
private:

public:
    /// Default constructor (disabled)
    Chest() = delete;

    /// Copy constructor (disabled)
    Chest(const Chest &) = delete;

    /// Assignment operator
    void operator=(const Chest &) = delete;

    Chest(Game* game, double c, double r, int w, int h, const std::wstring& filename, int tileHeight,
        const std::wstring& filename2, double mPA, int mPX, int mPY);
};



#endif //CHEST_H
