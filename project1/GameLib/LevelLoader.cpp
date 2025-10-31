/**
 * @file LevelLoader.cpp
 * @author Fatim
 */
 
#include "pch.h"
#include "LevelLoader.h"

#include <sstream>

#include "Game.h"
#include <unordered_map>
#include <vector>
#include "Container.h"

using namespace std;

/**
 * Constructor
 */
LevelLoader::LevelLoader()
{
}

/**
 * Takes the information from the level xml files and converts it into nodes to push as items via shared pointers
 * @param game
 * @param filename
 */
void LevelLoader::XmlLoad(Game* game, const std::string& filename)
{
    game->Clear();
    wxString path = wxString::FromUTF8(filename.c_str());

    wxXmlDocument document;
    if(!document.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    wxXmlNode* root = document.GetRoot();
    if (root->GetName() != "level") {
        wxMessageBox(L"The root is not a level");
        return;
    }
    wxString levelWidthStr, levelHeightStr, tileWidthStr, tileHeightStr;
    if (root->GetAttribute("width", &levelWidthStr) &&
        root->GetAttribute("height", &levelHeightStr) &&
        root->GetAttribute("tileheight", &tileHeightStr) &&
        root->GetAttribute("tilewidth", &tileWidthStr))
        {
            int levelWidth = wxAtoi(levelWidthStr);
            int levelHeight = wxAtoi(levelHeightStr);
            int tileWidth = wxAtoi(tileWidthStr);
            int tileHeight = wxAtoi(tileHeightStr);

            int levelSizeHeight = levelHeight * tileHeight;
            int levelSizeWidth = levelWidth * tileWidth;

            game->SetLevelSize(levelSizeWidth,levelSizeHeight);
            game->SetTileSize(tileWidth, tileHeight);
        }

    std::unordered_map<std::string, wxXmlNode*> declarations;

    wxXmlNode* child = root->GetChildren();
    while (child) {
        std::string name = child->GetName().ToStdString();

        if (name == "declarations") {
            wxXmlNode* declaration = child->GetChildren();
            while (declaration) {
                wxString id, width, height;
                if (declaration->GetAttribute("id", &id)) {
                    declarations[id.ToStdString()] = declaration;
                }
                declaration = declaration->GetNext();
            }
        }
        child = child->GetNext();
    }
    child = document.GetRoot()->GetChildren();
    while (child)
    {
        std::string name = child->GetName().ToStdString();
        if (name == "game")
        {
            int col = wxAtoi(child->GetAttribute("col", "0"));
            int row = wxAtoi(child->GetAttribute("row", "0"));
            int length = wxAtoi(child->GetAttribute("length", "0"));

            wxString content = child->GetNodeContent();
            std::istringstream stream(std::string(content.mb_str()));

            std::vector<int> letterValues;
            int val;

            while (stream >> val)
            {
                letterValues.push_back(val);
            }
            game->SetWordData(col, row, length, letterValues);
        }
        child = child->GetNext();
    }

    child = document.GetRoot()->GetChildren();
    while (child) {
        std::string name = child->GetName().ToStdString();

        if (name == "items") {
            wxXmlNode* item = child->GetChildren();
            while (item) {
                wxString id;
                if (item->GetAttribute("id", &id)) {
                    auto it = declarations.find(id.ToStdString());
                    if (it != declarations.end()) {
                        XmlItem(game, it->second, item, declarations);
                    }
                }
                item = item->GetNext();
            }
        }
        child = child->GetNext();
    }

}

/**
 *
 * Takes the attributes from the xml file and puts into the game through add functions
 * @param game
 * @param declaration
 * @param instance
 * @param declarations
 */
void LevelLoader::XmlItem(Game* game, wxXmlNode* declaration, wxXmlNode* instance,  const std::unordered_map<std::string, wxXmlNode*>& declarations)
{
    wxString type = declaration->GetName();

    wxString width, height, image, value;
    declaration->GetAttribute("width", &width);
    declaration->GetAttribute("height", &height);
    declaration->GetAttribute("image", &image);
    declaration->GetAttribute("value", &value);

    wxString col, row;
    instance->GetAttribute("col", &col);
    instance->GetAttribute("row", &row);

    int w = wxAtoi(width);
    int h = wxAtoi(height);
    int v = value.IsEmpty() ? 0 : wxAtoi(value);

    double c;
    col.ToDouble(&c);
    double r;
    row.ToDouble(&r);

    if (type == "letter") {
        game->AddLetter(game, c, r, w, h, image.ToStdWstring(), v);
        mMovableLetters.push_back(make_shared<int>(v));

    }
    else if (type == "given") {
        game->AddGiven(game, c, r, w, h, image.ToStdWstring(), v);
        mGivenTiles.push_back(make_shared<int>(v));

    }
    else if (type == "player") {
        wxString image1, image2, mouthPivotAngle, mouthPivotX, mouthPivotY;
        declaration->GetAttribute("image1", &image1);
        declaration->GetAttribute("image2", &image2);
        declaration->GetAttribute("mouth-pivot-angle", &mouthPivotAngle);
        declaration->GetAttribute("mouth-pivot-x", &mouthPivotX);
        declaration->GetAttribute("mouth-pivot-y", &mouthPivotY);

        double mPA;
        mouthPivotAngle.ToDouble(&mPA);
        int mPX = wxAtoi(mouthPivotX);
        int mPY = wxAtoi(mouthPivotY);

        game->AddPlayer(game, c, r, w, h, image1.ToStdWstring(), image2.ToStdWstring(), mPA, mPX, mPY);
    }
    else if (type == "tray") {
        wxString capacity;
        declaration->GetAttribute("capacity", &capacity);
        game->AddTray(game, c, r, w, h, image.ToStdWstring(), wxAtoi(capacity));
    }
    else if (type == "background") {
        game->SetBackground(image.ToStdString());

    }else if (type == "container") {
        wxString front;
        declaration->GetAttribute("front", &front);

        auto container = game->AddContainer(game, c, r, w, h, image.ToStdWstring(), front.ToStdWstring());

        // Process child elements (letters inside the container)
        wxXmlNode* child = instance->GetChildren();
        while (child) {
            wxString childId;
            if (child->GetName() == "letter" && child->GetAttribute("id", &childId)) {
                // Find the declaration for this letter
                auto letterDecl = declarations.find(childId.ToStdString());
                if (letterDecl != declarations.end()) {
                    // Get letter attributes
                    wxString letterWidth, letterHeight, letterImage, letterValue;
                    letterDecl->second->GetAttribute("width", &letterWidth);
                    letterDecl->second->GetAttribute("height", &letterHeight);
                    letterDecl->second->GetAttribute("image", &letterImage);
                    letterDecl->second->GetAttribute("value", &letterValue);

                    wxString letterCol, letterRow;
                    child->GetAttribute("col", &letterCol);
                    child->GetAttribute("row", &letterRow);

                    int lw = wxAtoi(letterWidth);
                    int lh = wxAtoi(letterHeight);
                    int lv = letterValue.IsEmpty() ? 0 : wxAtoi(letterValue);

                    double lc;
                    letterCol.ToDouble(&lc);
                    double lr;
                    letterRow.ToDouble(&lr);

                    // Create the letter and add it to the container
                    game->AddLetter(game, lc, lr, lw, lh, letterImage.ToStdWstring(), lv);
                    container->AddLetter(game->GetLastAddedLetter());
                }
            }
            child = child->GetNext();
        }

    }
}

