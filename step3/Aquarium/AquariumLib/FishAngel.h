/**
 * @file FishAngel.h
 * @author Cameron Schwindaman
 *
 * Class for a fish of type Angel
 */

#ifndef AQUARIUM_FISHANGEL_H
#define AQUARIUM_FISHANGEL_H

#include "Item.h"

/**
 * Class for a fish of type Angel
 */
class FishAngel : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    FishAngel() = delete;

    /// Copy constructor (disabled)
    FishAngel(const FishAngel &) = delete;

    /// Assignment operator
    void operator=(const FishAngel &) = delete;

    FishAngel(Aquarium* aquarium);
    void Draw(wxDC* dc) override;
    bool HitTest(int x, int y) override;
};

#endif //AQUARIUM_FISHANGEL_H
