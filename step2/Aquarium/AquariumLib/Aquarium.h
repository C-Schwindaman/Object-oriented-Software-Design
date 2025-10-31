/**
 * @file Aquarium.h
 * @author Cameron Schwindaman
 *
 * A class for our aquarium
 */
 
#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>

/**
 * A class for our aquarium
 */
class Aquarium {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

public:
    void OnDraw(wxDC* dc);
    Aquarium();
};

#endif //AQUARIUM_AQUARIUM_H
