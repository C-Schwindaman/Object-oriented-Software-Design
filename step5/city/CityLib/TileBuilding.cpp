/**
 * @file TileBuilding.cpp
 *
 * @author Anik Momtaz
 * @author Charles B. Owen
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "TileBuilding.h"
#include "City.h"
#include "MemberReport.h"

/// Number of slimed images for a building
const int BuildingSlimedNumImages = 6;

/// Image for ghost trap on lot
const std::wstring GhostTrapImage = L"ghost_trap.png";

/// How long each slimed image for a building lasts
const double BuildingSlimedImageDuration = 0.1;

/**
 * Constructor
 * @param city The city this is a member of
*/
TileBuilding::TileBuilding(City *city) : Tile(city)
{
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void TileBuilding::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mBuildingImageFile.empty())
    {
        mBuildingImageFile = file;
    }

    Tile::SetImage(file);
}

/**
 * Update the building animation in time
 * @param elapsed Elapsed time in seconds
 */
void TileBuilding::Update(double elapsed)
{
    Tile::Update(elapsed);

    if(mState == State::Slimed)
    {
        mSlimedImageDuration += elapsed;
        if(mSlimedImageDuration >= BuildingSlimedImageDuration)
        {
            mSlimedImageDuration -= BuildingSlimedImageDuration;

            // Iterate over the six images
            mSlimedImageIndex++;
            if (mSlimedImageIndex > 6)
            {
                mSlimedImageIndex = 1;
            }

            SetImage(mBuildingImageFile.substr(0, mBuildingImageFile.length() - 4) + L"_" + std::to_wstring(mSlimedImageIndex) + L".png");
        }
    }
}

/**
 * Cover the building in slime
 */
void TileBuilding::SetSlimed()
{
    // Set the slime state
    mState = State::Slimed;
    mSlimedImageDuration = 0;
    mSlimedImageIndex = 0;
}

/**
 * Trap a building in its ghost trap
 */
void TileBuilding::SetTrapped()
{
    if(mState == State::Slimed)
    {
        mState = State::Trapped;
        SetImage(GhostTrapImage);
    }
}

/**
 * Reset back to normal building state
 */
void TileBuilding::Reset()
{
    mState = State::Normal;
    SetImage(mBuildingImageFile);
}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileBuilding::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"building");
    itemNode->AddAttribute(L"file", mBuildingImageFile);

    return itemNode;
}

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileBuilding::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}

/**
 * Generate a report for this  tile.
 * @param report
*/
void TileBuilding::Report(std::shared_ptr<MemberReport> report)
{
    std::wstringstream str;
    str << L"Building - " << GetFile();

    report->SetReport(str.str());
}

// /**
//  * Reset back to normal building state
//  */
// void TileBuilding::FirehouseState()
// {
//     auto mState = L"Dispatch1";
//
//     if (mState != L"Idle") {
//
//     } else if (mState != L"Opening") {
//
//     } else if (mState == L"DispatchOne") {
//         mBuildingsSlimed[0]->Reset();
//         mBuildingsSlimed.clear();
//     } else if (mState == L"DispatchTwo") {
//
//     }
// }
