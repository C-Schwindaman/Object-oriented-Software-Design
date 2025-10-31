/**
 * @file DecorCastle.h
 * @author Cameron Schwindaman
 *
 * Class for a decor of type Castle
 */
 
#ifndef AQUARIUM_DECORCASTLE_H
#define AQUARIUM_DECORCASTLE_H

#include "Item.h"

/**
 * Class for a decor of type Castle
 */
class DecorCastle : public Item {
private:

public:
    /// Default constructor (disabled)
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle &) = delete;

    /// Assignment operator
    void operator=(const DecorCastle &) = delete;

    DecorCastle(Aquarium* aquarium);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //AQUARIUM_DECORCASTLE_H
