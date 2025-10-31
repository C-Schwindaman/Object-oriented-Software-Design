/**
 * @file Tray.h
 * @author Meghan Carter
 *
 *
 */

#ifndef TRAY_H
#define TRAY_H

#include "Item.h"
#include "Visitor.h"
#include <vector>


/**
 * Class representing a tray object in the game
 * This class derives from Item and represents an object in the game.
 */
class Tray :public Item {

private:
    /// the game itself
    Game* mGame;
    /// max number of letters that a player can hold
    int mCapacity = 4;
    /// the tray image
    std::unique_ptr<wxImage> mTrayImage;
    /// the bitmap for drawing tray
    std::unique_ptr<wxBitmap> mTrayBitmap;
    /// a vector of letters set of cast item to interact with player and spacebar, etc.
    std::vector<std::shared_ptr<Item>> mLetters;
    /// Height of tile
    int mTileHeight;
    /// boolean to see if the tray is full
    bool mFull = false;
    /// Current capacity of the Tray
    int mCurrentCapacity = 0;

protected:
    /// the location via column for letters in the tray
    double mColumn;
    /// the location via row for letters in the tray
    double mRow;
    /// the width of each letter according to the level xml files
    int mWidth;
    /// the height of each letter according to the level xml files
    int mHeight;
    /// member variable for bitmap to allow for drawing
    wxBitmap mBitmap;

public:
    Tray(Game* game, double c, double r, int w, int h, const std::wstring& filename, int maxStorage, int tileHeight);
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    bool AddLetter(std::shared_ptr<Item> letter) override;
    void RemoveLetter(std::shared_ptr<Item> letter);

    /**
    * Will return what each letter is based on the value that is provided
    * @param value
    * @return std::shared_ptr<Letter>
    */
    std::shared_ptr<Letter> GetLetterByValue(int value);

    /**
     * Clears the tray of all the letters
     */
    void Clear();

    /**
     * Takes the letters that are momentarily in tray and will move it into the word (container)
     * @param keyCode
     * @param x
     * @param y
     */
    void MoveGrabbedLetterToWord(int keyCode, double x, double y);

    /**
     * Will reset the letters to their original position in the alphabet based on the level xml locations
     */
    void ResetToOriginalPositions();

    /**
    * Accept a visitor
    * @param visitor The visitor to accept
    */
    void Accept(Visitor* visitor) override {
        visitor->VisitTray(this);
    }

    /**
    * Function that determines if clicked object is tray
    * @return bool
    */
    bool IsTray() const override {return true;}

    /**
    * Determines if the tray is full
    * @return bool
    */
    bool IsFull() const {return mLetters.size() >= mCapacity;};

    /**
     * returns the capacity of the tray
     * @return mCapacity
     */
    int GetCapacity() { return mCapacity; }

    /**
     * returns the amount of letters
     * @return mLetters.size()
     */
    int GetLetterCount() const { return mLetters.size(); }

    /**
     * returns the height of the tray
     * @return mHeight
     */
    double GetTrayHeight() const { return mHeight; }

    /**
     * returns the width of the tray
     * @return mWidth
     */
    double GetTrayWidth() const { return mWidth; }

};



#endif //TRAY_H
