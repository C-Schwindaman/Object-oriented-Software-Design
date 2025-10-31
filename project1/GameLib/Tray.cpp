/**
 * @file Tray.cpp
 * @author Meghan Carter
 */

#include "pch.h"
#include "Game.h"
#include "Tray.h"
#include <wx/string.h>
#include "Letter.h"
#include "ItemVisitor.h"

using namespace std;

/**
 * Constructor for tray
 * @param game
 * @param c
 * @param r
 * @param w
 * @param h
 * @param filename
 * @param maxStorage
 * @param tileHeight
 */
Tray::Tray(Game* game, double c, double r, int w, int h, const std::wstring& filename, int maxStorage, int tileHeight)
    : Item(game, filename), mColumn(c), mRow(r), mWidth(w), mHeight(h), mCapacity(maxStorage)
{
    mTileHeight = tileHeight;

    wxString path = L"images/" + filename;
    if (!mBitmap.LoadFile(path, wxBITMAP_TYPE_ANY))
    {
        std::wcout << L"Failed to load: " << path.ToStdWstring() << std::endl;
    }
}

/**
* The draw function for tray
* @param gc
*/
void Tray::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (mBitmap.IsOk())
    {
        double x = (mColumn) * mTileHeight;
        double y = (mRow + 1) * mTileHeight - mHeight;

        gc->DrawBitmap(mBitmap, x, y, mWidth, mHeight);
    }

    for (auto& letter : mLetters)
    {
        letter->Draw(gc);
    }
}

/**
* A function to see if a letter can be added to the tray
* Checks if item is a letter via visitor class and returns true if true
* @param letter
* @return bool
*/
bool Tray::AddLetter(std::shared_ptr<Item> letter)
{
    if (mCurrentCapacity < mCapacity && !mFull)
    {
        mLetters.push_back(letter);
        mCurrentCapacity++;
        return true;
    } else
    {
        mFull = true;
        // can put tray full message here?
        return false;
    }

}

/**
* Removes a letter from tray
* @param letter
*/
void Tray::RemoveLetter(std::shared_ptr<Item> letter)
{
    auto location = find(begin(mLetters), end(mLetters), letter);
    if (location != end(mLetters))
    {
        mLetters.erase(location);
        mCurrentCapacity--;
        mFull = false;
    }
}

/**
* Clears the tray of all the letters
*/
void Tray::Clear()
{
    mLetters.clear();
    mCurrentCapacity = 0;
    mFull = false;
}

/**
* Will return what each letter is based on the value that is provided
* @param value
* @return std::shared_ptr<Letter>
*/
std::shared_ptr<Letter> Tray::GetLetterByValue(int value)
{

    for (const auto& letter : mLetters)
    {
        if (letter->GetValue() == value)
        {

            return std::static_pointer_cast<Letter>(letter);
        }
    }
    return nullptr;
}

/**
* Takes the letters that are momentarily in tray and will move it into the word (container)
* @param keyCode
* @param x
* @param y
*/
void Tray::MoveGrabbedLetterToWord(int keyCode, double x, double y)
{
    char pressedLetter = static_cast<char>(keyCode);

    for (auto& letter : mLetters)
    {
        char tileLetter = letter->GetLetterValue();

        if (tileLetter == pressedLetter)
        {
            letter->SetLocation(x,y);
            mCurrentCapacity--;
            break;
        }
    }
}

/**
* Will reset the letters to their original position in the alphabet based on the level xml locations
*/
void Tray::ResetToOriginalPositions() {
    for (auto& letter : mLetters) {
        letter->SetLocation(letter->GetOriginalX(), letter->GetOriginalY());
    }
}
