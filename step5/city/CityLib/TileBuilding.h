/**
* @file TileBuilding.h
*
* @author Anik Momtaz
* @author Charles B. Owen
*
*  Class that implements a Building tile
*/

#pragma once

#include "Tile.h"

/**
*  A Building tile
*/
class TileBuilding : public Tile
{
private:
    /// The building image file
    std::wstring mBuildingImageFile;

    /// Possible building states
    enum class State {Normal, Slimed, Trapped};

    /// The current building state
    State mState = State::Normal;

    /// Current slimed image index
    int mSlimedImageIndex = 0;

    /// The duration for the current slimed image
    double mSlimedImageDuration = 0;

public:
    TileBuilding(City *city);

    ///  Default constructor (disabled)
    TileBuilding() = delete;

    ///  Copy constructor (disabled)
    TileBuilding(const TileBuilding &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Update(double elapsed) override;

    /**
     * Is this building slimed?
     * @return True if slimed
     */
    bool IsSlimed() {return mState == State::Slimed;}

    void SetTrapped();

    /**
     * Is this building trapped?
     * @return True if trapped
     */
    bool IsTrapped() {return mState == State::Trapped;}

    void SetImage(const std::wstring& file) override;

    void SetSlimed();

    void Reset();

    /**
     * Is this building normal?
     * @return True if normal
     */
    bool IsNormal() {return mState == State::Normal;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitBuilding(this); }
};

