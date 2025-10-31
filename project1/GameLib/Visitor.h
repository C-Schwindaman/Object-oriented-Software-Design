/**
 * @file Visitor.h
 * @author Serena Brown
 *
 *
 */

#ifndef BOGGLES_GAMELIB_VISITOR_H
#define BOGGLES_GAMELIB_VISITOR_H

/**
 * Up-call of letter
 */
class Letter;

/**
 * Up-call of player
 */
class Player;

/**
 * Up-call of tray
 */
class Tray;

/**
 * Up-call of container
 */
class Container;
/**
 * Up-call of sparty
 */
class Sparty;

/**
 * Visitor class that allows functions to traverse over other classes to act as a getter for info
 */
class Visitor

{
private:

protected:
    /**
    * Constructor
    */
    Visitor() {}
public:
    /**
     * Visitor Destructor
     */
    virtual ~Visitor() {}

    /**
     * Visitor function for Letter Class
     * @param letter
     */
    virtual void VisitLetter(std::shared_ptr<Letter> letter) {}

    /**
     * Visitor function for the Player Class
     * @param player
     */
    virtual void VisitPlayer(Player* player) {}

    /**
     * Visitor function for Tray
     * @param tray
     */
    virtual void VisitTray(Tray* tray) {}

    /**
     * Visitor class for the container
     * @param container
     */
    virtual void VisitContainer(Container* container) {}

    /**
     * Visitor class for sparty
     * @param sparty
     */
    virtual void VisitSparty(Sparty* sparty) {}
};

#endif //BOGGLES_GAMELIB_VISITOR_H
