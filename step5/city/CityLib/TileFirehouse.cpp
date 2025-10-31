/**
 * @file TileFirehouse.cpp
 *
 * @author Anik Momtaz
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "TileFirehouse.h"
#include "City.h"
#include "MemberReport.h"
#include "SlimedVisitor.h"
#include "TileBuilding.h"
#include "TrapVisitor.h"


/// Image for the Firehouse with the doors closed
const std::wstring FirehouseIdleImage = L"firehouse_idle.png";

/// Image of the Firehouse with the doors opening
const std::wstring FirehouseOpeningImage = L"firehouse_opening.png";

/// Image of the Firehouse with one Ectomobil dispatched
const std::wstring FirehouseDispatchedOneImage = L"firehouse_dispatched_one.png";

/// Image of the Firehouse with Ectomobils dispatched
const std::wstring FirehouseDispatchedTwoImage = L"firehouse_dispatched_two.png";

/// Duration the door opening image is displayed
const double FirehouseDoorOpeningTime = 1.0;

/// Duration the Ectomobils are displayed
const double EctomobilDisplayTime = 1.0;

/**
 * Constructor
 * @param city The city this is a member of
*/
TileFirehouse::TileFirehouse(City *city) : Tile(city)
{
    SetImage(FirehouseIdleImage);
    mCity = city;
}

/**
 * Update the building animation in time
 * @param elapsed Elapsed time in seconds
 */
void TileFirehouse::Update(double elapsed)
{
    Tile::Update(elapsed);

    // Get the number of slimed buildings
    SlimedVisitor visitor;
    mCity->Accept(&visitor);
    int buildingsSlimed = visitor.GetSlimedBuildings();

    // Get a visitor for trapping buildings
    TrapVisitor visitor2;

    if (mState == State::Opening) {
        mFirehouseImageDuration += elapsed;
        if (mFirehouseImageDuration >= FirehouseDoorOpeningTime) {
            if (!buildingsSlimed == 0) {
                // Proceed to Dispatch One
                mState = State::DispatchedOne;
                mFirehouseImageDuration = 0;
                SetImage(FirehouseDispatchedOneImage);
            }
        }
    }

    if (mState == State::DispatchedOne) {
        mFirehouseImageDuration += elapsed;
        if (mFirehouseImageDuration >= EctomobilDisplayTime) {
            if (buildingsSlimed == 1) {
                // Trap the building
                mCity->Accept(&visitor2);

                // Return to Idle state
                mState = State::Idle;
                mFirehouseImageDuration = 0;
                SetImage(FirehouseIdleImage);
            } else {
                // Proceed to Dispatch Two
                mState = State::DispatchedTwo;
                mFirehouseImageDuration = 0;
                SetImage(FirehouseDispatchedTwoImage);
            }
        }
    }

    if (mState == State::DispatchedTwo) {
        mFirehouseImageDuration += elapsed;
        if (mFirehouseImageDuration >= EctomobilDisplayTime) {
            // Trap all buildings
            mCity->Accept(&visitor2);

            // Return to Idle state
            mState = State::Idle;
            mFirehouseImageDuration = 0;
            SetImage(FirehouseIdleImage);
        }
    }
}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileFirehouse::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"firehouse");

    return itemNode;
}

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileFirehouse::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
}

/**
 * Generate a report for this  tile.
 * @param report
*/
void TileFirehouse::Report(std::shared_ptr<MemberReport> report)
{
    std::wstringstream str;
    str << L"Building - Firehouse";

    report->SetReport(str.str());
}

/**
 * Open the firehouse if buildings are slimed
 */
void TileFirehouse::SetOpening()
{
    // Get the number of slimed buildings
    SlimedVisitor visitor;
    mCity->Accept(&visitor);
    auto buildingsSlimed = visitor.GetSlimedBuildings();

    if (!buildingsSlimed == 0)
    {
        mState = State::Opening;
        mFirehouseImageDuration = 0;
        SetImage(FirehouseOpeningImage);
    }
}