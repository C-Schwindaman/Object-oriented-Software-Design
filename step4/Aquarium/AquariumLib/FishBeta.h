/**
 * @file FishBeta.h
 * @author Cameron Schwindaman
 *
 * Class for a fish of type Beta
 */
 
#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H

#include "Fish.h"

/**
 * Class for a fish of type Beta
 */
class FishBeta : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;

    FishBeta(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //AQUARIUM_FISHBETA_H
