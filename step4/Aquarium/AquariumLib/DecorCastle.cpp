/**
 * @file DecorCastle.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <string>
#include "DecorCastle.h"
#include "Aquarium.h"

using namespace std;

/// Decor filename
const wstring DecorCastleImageName = L"images/castle.png";

/**
 * Constructor
 * @param aquarium Aquarium this decor is a member of
 */
DecorCastle::DecorCastle(Aquarium *aquarium) : Item(aquarium, DecorCastleImageName)
{
}

/**
 * Save this decor to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* DecorCastle::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);

    itemNode->AddAttribute(L"type", L"castle");

    return itemNode;
}