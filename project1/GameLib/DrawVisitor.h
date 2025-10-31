/**
 * @file DrawVisitor.h
 * @author Fatim
 *
 * A class of drawing visitors
 */
 
#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include "Letter.h"
#include "Player.h"
#include "Tray.h"
#include "Container.h"

/**
 * A class of drawing visitors
 */
class DrawVisitor : public Visitor {
private:
    /// The graphics context to draw on
    std::shared_ptr<wxGraphicsContext> mGraphics;

public:
    /**
     * Draws on the given graphics context
     * @param graphics The graphics context to draw on
     */
    DrawVisitor(std::shared_ptr<wxGraphicsContext> graphics) : mGraphics(graphics) {}

    /**
     * Visit a Letter item
     * @param letter The Letter we are visiting
     */
    void VisitLetter(std::shared_ptr<Letter> letter) override {
        letter->Draw(mGraphics);
    }

    /**
     * Visit a Container item
     * @param container The Container we are visiting
     */
    void VisitContainer(Container* container) override {
        container->Draw(mGraphics);
    }

    /**
     * Visit a Player item
     * @param player The Player we are visiting
     */
    void VisitPlayer(Player* player) override {
        player->Draw(mGraphics);
    }

    /**
     * Visit a Tray item
     * @param tray The Tray we are visiting
     */
    void VisitTray(Tray* tray) override {
        tray->Draw(mGraphics);
    }

};



#endif //DRAWVISITOR_H
