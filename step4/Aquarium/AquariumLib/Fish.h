/**
 * @file Fish.h
 * @author Cameron Schwindaman
 *
 * Base class for a fish
 */
 
#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H

#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:
    void Update(double elapsed);
    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    void XmlLoad(wxXmlNode* node) override;

    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

protected:
    Fish(Aquarium* aquarium, const std::wstring& filename);
    void SetSpeedX(double speed);
    void SetSpeedY(double speed);
};

#endif //AQUARIUM_FISH_H
