/**
 * @file UpdateVisitor.h
 * @author Fatim
 *
 *
 */
 
#ifndef UPDATEVISITOR_H
#define UPDATEVISITOR_H
#include "Letter.h"
#include "Player.h"
#include "Tray.h"
#include "Sparty.h"

/**
 * subclass of visitor; focuses on the update function in each class being visited
 */
class UpdateVisitor : public Visitor {
private:
    /// member variable that keeps track of the elapsed time
    double mElapsed;

public:
    /**
     * Constructor for the UpdateVisitor that assigns variable 'elapsed' to member variable 'mElapsed'
     * @param elapsed
     */
    UpdateVisitor(double elapsed) : mElapsed(elapsed) {}

    /**
     * Visitor function for Letter Class that updates letter
     * @param letter
     */
    void VisitLetter(std::shared_ptr<Letter> letter) override {
        letter->Update(mElapsed);
    }

    /**
     * Visitor function for the Player Class that updates player
     * @param player
     */
    void VisitPlayer(Player* player) override {
        player->Update(mElapsed);
    }

    /**
     * Visitor function for Tray that updates tray
     * @param tray
     */
    void VisitTray(Tray* tray) override {
        tray->Update(mElapsed);
    }

    /**
     * Visitor function for Sparty that updates sparty
     * @param sparty
     */
    void VisitSparty(Sparty* sparty) override {
        sparty->Update(mElapsed);
    }
};


#endif //UPDATEVISITOR_H
