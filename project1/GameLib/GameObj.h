/**
 * @file GameObj.h
 * @author Fatim
 *
 * A class for game objects
 */
 
#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "GameView.h"

class Game;

/**
 * A class for game objects
 */
class GameObj : public Item  {
private:

public:
    /**
     * Constructor
     * @param game The game this object is a member of
     */
    GameObj(Game* game);

    /**
     * Destructor
     */
    virtual ~GameObj();

    /// Default constructor (disabled)
    GameObj() = delete;
    /// Copy constructor (disabled)
    GameObj(const GameObj&) = delete;
    /// Assignment operator
    void operator=(const GameObj&) = delete;
};

#endif //GAMEOBJ_H
