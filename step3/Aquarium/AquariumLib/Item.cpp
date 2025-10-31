/**
 * @file Item.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

/// Distance other fish traverse when Finfluencer is active
const double MoveDistance = 100;

/// Width of aquarium
const int WIDTH = 1000;

/// Height of aqaurium
const int HEIGHT = 800;


/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 */
Item::Item(Aquarium *aquarium) : mAquarium(aquarium)
{
}

/**
 * Moves target item in relation to the source item
 * @param source The source item
 * @param target The target item
 */
void Item::Move(std::shared_ptr<Item> source, std::shared_ptr<Item> target)
{
    {
        double dx = target->GetX() - source->GetX();
        double dy = target->GetY() - source->GetY();
        double dist = sqrt(dx * dx + dy * dy);

        if (dist == 0) return;

        double moveDistance = (dist < MoveDistance) ? dist : MoveDistance;

        double factor = moveDistance / dist;
        double newX = target->GetX() + dx * factor;
        double newY = target->GetY() + dy * factor;

        int width = WIDTH;
        int height = HEIGHT;

        if (newX < 0 || newX > width || newY < 0 || newY > height)
        {
            return;
        }

        target->SetLocation(newX, newY);
    }
}

