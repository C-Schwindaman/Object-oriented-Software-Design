/**
 * @file FishAngel.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <string>
#include "FishAngel.h"
#include "Aquarium.h"

using namespace std;

/// Maximum speed in pixels per second
const double MaxSpeed = 30;

/// Minimum speed in pixels per second
const double MinSpeed = 10;

/// Fish filename
const wstring FishAngelImageName = L"images/angelfish.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishAngel::FishAngel(Aquarium *aquarium) : Fish(aquarium, FishAngelImageName)
{
    std::uniform_real_distribution<> distribution(MinSpeed, MaxSpeed);
    this->SetSpeedX(distribution(aquarium->GetRandom()));
    this->SetSpeedY(distribution(aquarium->GetRandom()));
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishAngel::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);

    itemNode->AddAttribute(L"type", L"angel");

    return itemNode;
}