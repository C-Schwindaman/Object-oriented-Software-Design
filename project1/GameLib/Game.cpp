/**
* @file Game.cpp
 * @author Caleb Blackwell, Serena Brown
 */

#include "pch.h"
#include <wx/graphics.h>
#include <unordered_map>
#include <random>
#include "Game.h"
#include "Player.h"
#include "LevelLoader.h"
#include "Letter.h"
#include "Given.h"
#include "Tray.h"
#include "Visitor.h"
#include "DrawVisitor.h"
#include "UpdateVisitor.h"
#include "SolveVisitor.h"
#include "PopUpWindow.h"
#include "HeadButtVisitor.h"
#include "Container.h"
#include "Sparty.h"

using namespace std;

/**
 * Constructor
 */
Game::Game(): mLevelWidth(), mLevelHeight(), mTray(nullptr), mTrayPosition(0,0), mTrayCapacity(0), mGrabbedItem(nullptr)
{
    mBackground = make_unique<wxBitmap>(
            L"images/background.png", wxBITMAP_TYPE_ANY);
    mScoreboard.SetGame(this);
}

/**
 * Draw the game
 * @param gc The graphics context to draw on
 * @param width Width of the game
 * @param height Height of the game
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height)
{

    int pixelWidth = mLevelWidth;  // Virtual width of the project area
    int pixelHeight = mLevelHeight;  // Virtual height of the project area

    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = (height - pixelHeight * mScale) / 2.0;

    gc->PushState();
    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);

    gc->DrawBitmap(*mBackground, 0, 0, pixelWidth, pixelHeight);

    // Draw the scoreboard
    mScoreboard.Draw(gc);

    // for (const auto& item : mItems)
    // {
    //     item->Draw(gc);
    // }
    //
    // gc->PopState();
    DrawVisitor visitor(gc);
    for (const auto& item : mItems)
    {
        item->Accept(&visitor);
    }

    gc->PopState();
}



/**
 * Clears the game data.
 * Deletes all known items in the game.
 */
void Game::Clear()
{
    mItems.clear();
    mMovableLetters.clear();
    mGivenTiles.clear();
    mGameWord = GameWord();
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
 */
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            if ((*i)->IsLetter())
            {
                continue;
            }

            return *i;
        }
    }
    return nullptr;
}

/**
 * Sets the background of the game
 * @param filename The filename of the background
 */
void Game::SetBackground(const std::string& filename)
{
    wxString newFilename = L"images/" + filename;
    mBackground = make_unique<wxBitmap>(
        newFilename, wxBITMAP_TYPE_ANY);
}

/**
 * Adds a player to the game
 * @param game The game this Player belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Player
 * @param h Height of the Player
 * @param filename Filename of image1
 * @param filename2 Filename of image2
 * @param mPA Mouth pivot angle
 * @param mPX Mouth pivot X
 * @param mPY Mouth pivot Y
 */
void Game::AddPlayer(Game* game, double c, double r, int w, int h, const std::wstring& filename, const std::wstring& filename2, double mPA, int mPX, int mPY)
{
    auto player = std::make_shared<Player>(game, c, r, w, h, filename, mTileHeight, filename2, mPA, mPX, mPY);
    mItems.push_back(player);
    mPlayer = player;
}

/**
 * Adds a letter to the game
 * @param game The game this Letter belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Letter
 * @param h Height of the Letter
 * @param filename Filename of image
 * @param value Value of the letter
 */
void Game::AddLetter(Game* game, double c, double r, int w, int h, const std::wstring& filename, int value)
{
    auto letter = std::make_shared<Letter>(game, c, r, w, h, filename, value);
    mItems.push_back(letter);
    mMovableLetters.push_back(letter);
    mLastAddedLetter = letter;
}

/**
 * Adds a given to the game
 * @param game The game this Given belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Given
 * @param h Height of the Given
 * @param filename Filename of image
 * @param value Value of the Given
 */
void Game::AddGiven(Game*game, double c, double r, int w, int h, const std::wstring& filename, int value)
{
    auto given = std::make_shared<Letter>(game, c, r, w, h, filename, value);
    mItems.push_back(given);
    mGivenTiles.push_back(given);
}

/**
 * Adds a tray to the game
 * @param game The game this Tray belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Tray
 * @param h Height of the Tray
 * @param filename Filename of image
 * @param capacity Capacity of the Tray
 */
void Game::AddTray(Game* game, double c, double r, int w, int h, const std::wstring& filename, int capacity)
{
    auto tray = std::make_shared<Tray>(game, c, r, w, h, filename, capacity, mTileHeight);
    mItems.push_back(tray);
    mTray = tray;
    mTrayPosition = wxPoint2DDouble(c * mTileWidth, r * mTileHeight);
    mTrayCapacity = 0;
    mMaxTrayCapacity = capacity;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{

    UpdateVisitor visitor(elapsed);
    for (auto& item : mItems) {
        item->Accept(&visitor);
    }

    // Update the scoreboard
    mScoreboard.Update(elapsed);
}

/**
 * Loads the level of the game
 * @param filename The filename of the level
 */
void Game::LoadLevel(const std::string& filename)
{
    LevelLoader loader;
    loader.XmlLoad(this, filename);
}

/**
 * Resets the scoreboard of the game
 */
void Game::ResetScoreboard() {
    mScoreboard.Reset();
}

/**
 * Handle a mouse click
 * @param x X location clicked on
 * @param y Y location clicked on
 */
void Game::OnLeftDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    std::shared_ptr<Item> letterClicked = nullptr;
    for (auto i = mItems.rbegin(); i != mItems.rend(); ++i)
    {
        if ((*i)->HitTest(oX, oY) && (*i)->IsLetter())
        {
            letterClicked = *i;
            break;
        }
    }

    if (letterClicked)
    {
        mSelectedLetter = letterClicked;
    }
    else
    {
        mSelectedLetter = nullptr;
    }

    if (mPlayer)
    {
        mPlayer->SetPlayerLocation(oX, oY);
    }
}

/**
 * Sets the size of the level
 * @param width Width of the level
 * @param height Height of the level
 */
void Game::SetLevelSize(int width, int height)
{
    mLevelWidth = width;
    mLevelHeight = height;
}

/**
 * Sets the size of the tile
 * @param width Width of the tile
 * @param height Height of the tile
 */
void Game::SetTileSize(int width, int height)
{
    mTileWidth = width;
    mTileHeight = height;
}

/**
 * Sets the level data of the game
 * @param givenTiles Given tiles of the game
 * @param movableLetters Movable letters of the game
 */
void Game::SetLevelData(const std::vector<std::shared_ptr<Letter>>& givenTiles,
                        const std::vector<std::shared_ptr<Letter>>& movableLetters) {
    mGivenTiles = givenTiles;
    mMovableLetters = movableLetters;
}

/**
 * Solves the game by moving tiles to correct spot
 */
void Game::SolveLevel()
{
    if (mMovableLetters.empty() || mGameWord.GetLength() == 0) {
        return;
    }

    SolveVisitor visitor(mGameWord, mGivenTiles, mTileWidth, mTileHeight);

    for (auto& letter : mMovableLetters)
    {
        letter->Accept(&visitor);
    }
}

/**
 * Moves selected letter to the tray
 * @param letter The letter to be moved
 */
void Game::MoveLetterToTray(std::shared_ptr<Item> letter)
{
    if (!mTray) return;

    if (mTray->AddLetter(letter))
    {
        double xMin = mTrayPosition.m_x + mTileWidth;
        double yMin = mTrayPosition.m_y - (mTray->GetTrayHeight()) + mTileHeight;
        double xMax = mTrayPosition.m_x + (mTray->GetTrayWidth()) - mTileWidth;
        double yMax = mTrayPosition.m_y - mTileHeight;


        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distX(xMin, xMax);
        std::uniform_real_distribution<> distY(yMin, yMax);

        double randomX = distX(gen);
        double randomY = distY(gen);

        letter->SetLocation(randomX, randomY);

        auto it = std::find_if(mItems.begin(), mItems.end(),
            [&letter](const std::shared_ptr<Item>& item) {
                return item == letter;  // Ensure we are comparing the exact same object
            });

        if (it != mItems.end())
        {
            mItems.erase(it);
        }

        mTrayCapacity++;
    }
}

/**
 * Players initiates a headbutt on nearest container
 * @return True if the container was headbutted
 */
bool Game::HeadbuttContainer()
{
    if (!mPlayer)
    {
        return false;
    }

    // Find the nearest container
    std::shared_ptr<Item> nearestContainer = nullptr;
    double nearestDistance = std::numeric_limits<double>::max();

    double playerX = mPlayer->GetX();
    double playerY = mPlayer->GetY();

    for (auto& item : mItems)
    {
        if (item->IsContainer())
        {
            double dx = item->GetX() - playerX;
            double dy = item->GetY() - playerY;
            double distance = std::sqrt(dx * dx + dy * dy);

            if (distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestContainer = item;
            }
        }
    }

    if (nearestContainer)
    {

        mPlayer->SetPlayerLocation(nearestContainer->GetX(), nearestContainer->GetY());


        const double HeadbuttDistance = 100.0;
        if (nearestDistance < HeadbuttDistance)
        {
            HeadButtVisitor visitor;
            nearestContainer->Accept(&visitor);
            return visitor.WasContainerHeadbutted();
        }
    }

    return false;
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(Visitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
    if (mSparty)
    {
        mSparty->Accept(visitor);
    }
}

/**
 * Adds a container to the game
 * @param game The game this Container belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Container
 * @param h Height of the Container
 * @param filename Filename of image
 * @param filename2 Filename of front
 * @return
 */
std::shared_ptr<Container> Game::AddContainer(Game* game, double c, double r, int w, int h,
                                              const std::wstring& filename, const std::wstring& filename2)
{
    auto container = std::make_shared<Container>(game, filename, filename2);
    container->SetLocation(c * mTileWidth, r * mTileHeight);
    mItems.push_back(container);
    return container;
}

/**
 * Checks if the Tray is full
 * @return True if it is full
 */
bool Game::IsTrayFull() const
{
    return mTrayCapacity >= mMaxTrayCapacity;
}

/**
 * Adds an item to the game
 * @param item Item to be added
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Checks if the letters are correct
 * @param letter Letter to be checked
 * @param position Position of letter
 * @return True if the letter is correct
 */
bool Game::IsCorrectLetter(std::shared_ptr<Letter> letter, int position)
{
    if (!mIsLevelThree || !letter)
        return true;
    const std::vector<int> solutionValues = {5, 17, 8, 3, 0, 25};

    if (position >= 0 && position < solutionValues.size())
    {
        return letter->GetValue() == solutionValues[position];
    }

    return false;
}

/**
 * Gets the players current position
 * @return X and Y coordinates of the player
 */
wxPoint2DDouble Game::GetPlayerPosition() const
{
    if (mPlayer)
    {
        return wxPoint2DDouble(mPlayer->GetX(), mPlayer->GetY());
    }

    return wxPoint2DDouble(0, 0);
}

/**
 * Adds a penalty minute to the scoreboard
 */
void Game::AddPenaltyMinute()
{
    if (mIsLevelThree)
    {
        mPenaltyMinutes++;

        mScoreboard.AddPenaltyMinute();
    }
}

/**
 * Gets the width of the grid
 * @return The width of the grid
 */
int Game::GetGridWidth() const
{
    return mLevelWidth / mTileWidth;
}

/**
 * Gets a letter from tray by its value
 * @param value The value of the letter
 * @return A pointer to the letter
 */
std::shared_ptr<Letter> Game::GetLetterFromTrayByValue(int value)
{
    if (mTray)
    {
        return mTray->GetLetterByValue(value);
    }
    return nullptr;
}

/**
 * The player begin its opening sequence
 */
void Game::StartOpeningSequence() const
{
    mPlayer->StartOpening();
}

/**
 * Moves a letter from the tray to the word
 * @param key The key of the letter
 */
void Game::LetterFromTrayToWord(char key)
{
    if (mSelectedIndex == -1 || !mTray) return;

    const GameWord& word = GetWord();
    int expectedValue = word.GetLetterValues()[mSelectedIndex];
    char expectedLetter = static_cast<char>(expectedValue + 'A');

    int col = word.GetStartCol() + mSelectedIndex;
    int row = word.GetStartRow();

    double x = col * GetTileWidth();
    double y = row * GetTileHeight();

    mTray->MoveGrabbedLetterToWord(key, x, y);
    ClearSelectedIndex();

    mTrayCapacity--;
}

/**
 * Resets tray letters to original positions
 */
void Game::ResetTrayLetters()
{
    mTray->ResetToOriginalPositions();
}

/**
 * Sets the word data of the game
 * @param col Column position
 * @param row Row position
 * @param length Length of the word
 * @param values Values of the word
 */
void Game::SetWordData(int col, int row, int length, const std::vector<int>& values)
{
    mGameWord = GameWord(col, row, length, values);

}