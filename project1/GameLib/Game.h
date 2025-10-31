/**
* @file Game.h
 * @author Caleb Blackwell, Serena Brown
 *
 * A class for the game
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include "Scoreboard.h"
#include "Item.h"
#include "Player.h"
#include "GameWord.h"

class Given;

/**
 * A class for the game
 */
class Game {
private:
    /// Bitmap of the game background
    std::unique_ptr<wxBitmap> mBackground;
    /// Width of screen level
    int mLevelWidth;
    /// Height of screen level
    int mLevelHeight;
    /// Scale of the screen
    double mScale;
    /// X offset of the screen
    double mXOffset;
    /// Y offset of the screen
    double mYOffset;
    /// Store the Player object
    std::shared_ptr<Player> mPlayer;
    /// Store the Tray Object
    std::shared_ptr<Tray> mTray;
    /// Store the mGrabbedItem
    std::shared_ptr<Item> mGrabbedItem;
    /// Position of tray
    wxPoint2DDouble mTrayPosition;
    /// Capacity of tray
    int mTrayCapacity = 0;
    /// Maximum capacity of tray
    int mMaxTrayCapacity = 0;
    /// Width of the game
    int mWidth = 0;
    /// Height of the game
    int mHeight = 0;
    /// Width of tile
    int mTileWidth;
    /// Height of tile
    int mTileHeight;
    /// Penalty minutes added
    int mPenaltyMinutes = 0;
    /// Is it level three?
    bool mIsLevelThree = false;
    /// Pointer to the selected letter
    std::shared_ptr<Item> mSelectedLetter;
    /// List of items in the game
    std::vector<std::shared_ptr<Item>> mItems;
    /// GameWord instance
    GameWord mGameWord;
    /// Selected index of the game
    int mSelectedIndex = -1;
    /// Scoreboard instance
    Scoreboard mScoreboard;
    /// List of given tiles
    std::vector<std::shared_ptr<Letter>> mGivenTiles;
    /// List of movable letters
    std::vector<std::shared_ptr<Letter>> mMovableLetters;
    /// Pointer to the last added letter
    std::shared_ptr<Letter> mLastAddedLetter;
    /// Pointer to Sparty
    std::shared_ptr<Sparty> mSparty;
    /// Are we awating the headbutt?
    bool mAwaitingHeadbutt = false;
    /// A pointer to the target container
    std::shared_ptr<Item> mTargetContainer = nullptr;
public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Clear();
    std::shared_ptr<Item> HitTest(int x, int y);
    void SetBackground(const std::string& filename);
    void AddPlayer(Game* game, double c, double r, int w, int h, const std::wstring& filename,
                   const std::wstring& filename2, double mPA, int mPX, int mPY);
    void AddLetter(Game* game, double c, double r, int w, int h, const std::wstring& filename, int value);
    void AddGiven(Game* game, double c, double r, int w, int h, const std::wstring& filename, int value);
    void AddTray(Game* game, double c, double r, int w, int h, const std::wstring& filename, int capacity);
    void Update(double elapsed);
    void OnLeftDown(int x, int y);
    void SetLevelSize(int height, int width);
    void SetTileSize(int width, int height);
    void LoadLevel(const std::string& filename);
    void ResetScoreboard();
    void MoveLetterToTray(std::shared_ptr<Item> letter);
    std::shared_ptr<Container> AddContainer(Game* game, double c, double r, int w, int h,
                              const std::wstring& filename, const std::wstring& filename2);
    bool IsTrayFull() const;
    void StartOpeningSequence() const;
    void LetterFromTrayToWord(char key);
    void ResetTrayLetters();

    /**
     * Getter for the X offset of the game
     * @return The X offset of the game
     */
    double GetXOffset() const { return mXOffset; }

    /**
     * Getter for the Y offset of the game
     * @return The Y offset of the game
     */
    double GetYOffset() const { return mYOffset; }

    /**
     * Getter for the scale of the game
     * @return The scale of the game
     */
    double GetScale() const { return mScale; }

    /**
     * FOR TESTING ONLY
     * @return Level width
     */
    int GetLevelWidth() const { return mLevelWidth; }
    /**
     * FOR TESTING ONLY
     * @return Level height
     */
    int GetLevelHeight() const { return mLevelHeight; }
    /**
     *FOR TESTING ONLY
     * @return Tile width
     */
    int GetTileWidth() const { return mTileWidth; }
    /**
     * FOR TESTING ONLY
     * @return Tile height in the game
     */
    int GetTileHeight() const { return mTileHeight; }

    int GetGridWidth() const;

    /**
     * FOR TESTING ONLY
     * @return Items in the game
     */
    std::vector<std::shared_ptr<Item>> GetItems() const { return mItems; }

    /**
     * Getter for the player of the game
     * @return The player of the game
     */
    std::shared_ptr<Player> GetPlayer() { return mPlayer; }

    /**
     * Checks the value of an item
     * @param item The item to check
     * @return The value of an item
     */
    int GetValue(const std::shared_ptr<Item>& item) const { return item ? item->GetValue() : -1; }

    /**
     * Gets the currently selected letter
     * @return The currently selected letter
     */
    std::shared_ptr<Item> GetSelectedLetter() const { return mSelectedLetter; }

    /**
     * Clears the currently selected letter
     */
    void ClearSelectedLetter() { mSelectedLetter = nullptr; }

    void SolveLevel();
    void SetLevelData(const std::vector<std::shared_ptr<Letter>>& givenTiles,
                      const std::vector<std::shared_ptr<Letter>>& movableLetters);
    void Accept(Visitor *visitor);
    bool HeadbuttContainer();
    void AddItem(std::shared_ptr<Item> item);
    void AddPenaltyMinute();

    /**
     * Gets the penalty minutes added
     * @return The penalty minutes added
     */
    int GetPenaltyMinutes() const { return mPenaltyMinutes; }

    /**
     * Sets the level to level three
     * @param isLevelThree True if it is level three
     */
    void SetLevelThree(bool isLevelThree) { mIsLevelThree = isLevelThree; }

    /**
     * Checks if the level is level three
     * @return True if it is level three
     */
    bool IsLevelThree() const { return mIsLevelThree; }

    bool IsCorrectLetter(std::shared_ptr<Letter> letter, int position);
    wxPoint2DDouble GetPlayerPosition() const;
    std::shared_ptr<Letter> GetLetterFromTrayByValue(int value);
    void SetWordData(int col, int row, int length, const std::vector<int>& values);

    /**
     * Gets the game word being guessed
     * @return The game word being guessed
     */
    const GameWord GetWord() const { return mGameWord; }

    /**
     * Sets the selected index
     * @param index The value of the selected index
     */
    void SetSelectedIndex(int index) {mSelectedIndex = index; }

    /**
     * Clears the selected index
     */
    void ClearSelectedIndex() { mSelectedIndex = -1; }

    /**
     * Gets the last letter that was added
     * @return The last letter that was added
     */
    std::shared_ptr<Letter> GetLastAddedLetter() const { return mLastAddedLetter; }
};



#endif //GAME_H
