/**
 * @file Aquarium.h
 * @author Cameron Schwindaman
 *
 * A class for our aquarium
 */
 
#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>

class Item;

/**
 * A class for our aquarium
 */
class Aquarium {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Aquarium();
    void OnDraw(wxDC* dc);
    void Add(std::shared_ptr<Item> item);
    std::shared_ptr<Item> HitTest(int x, int y);
    void MoveToEnd(std::shared_ptr<Item> item);
    void MoveItems(std::shared_ptr<Item> source);
};

#endif //AQUARIUM_AQUARIUM_H
