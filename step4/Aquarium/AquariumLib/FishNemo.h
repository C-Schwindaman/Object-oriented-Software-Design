/**
* @file FishNemo.h
 * @author Cameron Schwindaman
 *
 * Class for a fish of type Nemo
 */

#ifndef AQUARIUM_FISHNEMO_H
#define AQUARIUM_FISHNEMO_H

#include "Fish.h"

/**
 * Class for a fish of type Nemo
 */
class FishNemo : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishNemo() = delete;

    /// Copy constructor (disabled)
    FishNemo(const FishNemo &) = delete;

    /// Assignment operator
    void operator=(const FishNemo &) = delete;

    FishNemo(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //AQUARIUM_FISHNEMO_H
