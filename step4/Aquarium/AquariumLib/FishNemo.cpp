/**
 * @file FishNemo.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <string>
#include "FishNemo.h"
#include "Aquarium.h"

using namespace std;

/// Maximum speed in pixels per second
const double MaxSpeed = 70;

/// Minimum speed in pixels per second
const double MinSpeed = 40;

/// Fish filename
const wstring FishNemoImageName = L"images/nemo.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishNemo::FishNemo(Aquarium *aquarium) : Fish(aquarium, FishNemoImageName)
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
wxXmlNode* FishNemo::XmlSave(wxXmlNode* node)
{
    auto itemNode = Fish::XmlSave(node);

    itemNode->AddAttribute(L"type", L"nemo");

    return itemNode;
}