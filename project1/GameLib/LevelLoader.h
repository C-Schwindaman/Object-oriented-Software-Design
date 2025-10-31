/**
 * @file LevelLoader.h
 * @author Fatim
 *
 *
 */
 
#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include <string>
#include <wx/xml/xml.h>

/**
 * Up-call of class given
 */
class Given;

/**
 * Up-call of class letter
 */
class Letter;

/**
 * Up-call of class game
 */
class Game;

/**
 * Takes info from xml files and puts into game
 */
class LevelLoader {
private:
    /// vector of shared pointer of given tiles
    std::vector<std::shared_ptr<int>> mGivenTiles;
    /// vector of shared pointer of movable letters
    std::vector<std::shared_ptr<int>> mMovableLetters;

public:
    LevelLoader();
    void XmlLoad(Game* game, const std::string& filename);
    void XmlItem(Game* game, wxXmlNode* declaration, wxXmlNode* instance, const std::unordered_map<std::string, wxXmlNode*>& declarations);

    /**
     * returns the immovable letters
     * @return mGivenTiles
     */
    const std::vector<std::shared_ptr<int>>& GetGivenTiles() const { return mGivenTiles; }

    /**
     * returns the letters that are able to move
     * @return mMovableLetters
     */
    const std::vector<std::shared_ptr<int>>& GetMovableLetters() const { return mMovableLetters; }
};



#endif //LEVELLOADER_H
