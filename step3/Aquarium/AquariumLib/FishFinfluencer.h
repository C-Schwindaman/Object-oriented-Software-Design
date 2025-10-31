/**
* @file FishFinfluencer.h
 * @author Cameron Schwindaman
 *
 * Class for a fish of type Finfluencer
 */

#ifndef AQUARIUM_FISHFINFLUENCER_H
#define AQUARIUM_FISHFINFLUENCER_H

#include "Item.h"

/**
 * Class for a fish of type Finfluencer
 */
class FishFinfluencer : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The underlying active fish image
    std::unique_ptr<wxImage> mActiveImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

    /// The bitmap we can display for this active fish
    std::unique_ptr<wxBitmap> mActiveBitmap;

    /// Displays whether Finfluencer is active
    bool mIsActive = false;

public:
    /// Default constructor (disabled)
    FishFinfluencer() = delete;

    /// Copy constructor (disabled)
    FishFinfluencer(const FishFinfluencer &) = delete;

    /// Assignment operator
    void operator=(const FishFinfluencer &) = delete;

    FishFinfluencer(Aquarium* aquarium);
    void Draw(wxDC* dc) override;
    bool HitTest(int x, int y) override;
    void Active();
    void Deactive();
    void Move(std::shared_ptr<Item> target, std::shared_ptr<Item> source) override;
};

#endif //AQUARIUM_FISHFINFLUENCER_H
