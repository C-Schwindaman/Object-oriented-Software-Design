/**
 * @file FishAngel.h
 * @author Cameron Schwindaman
 *
 * Class for a fish of type Angel
 */

#ifndef AQUARIUM_FISHANGEL_H
#define AQUARIUM_FISHANGEL_H

#include "Fish.h"

/**
 * Class for a fish of type Angel
 */
class FishAngel : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishAngel() = delete;

    /// Copy constructor (disabled)
    FishAngel(const FishAngel &) = delete;

    /// Assignment operator
    void operator=(const FishAngel &) = delete;

    FishAngel(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //AQUARIUM_FISHANGEL_H
