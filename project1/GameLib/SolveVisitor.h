/**
 * @file SolveVisitor.h
 * @author Serena
 *
 *
 */

#ifndef BOGGLES_GAMELIB_SOLVEVISITOR_H
#define BOGGLES_GAMELIB_SOLVEVISITOR_H

#include "Visitor.h"
#include "GameWord.h"
#include "Given.h"
#include "Letter.h"

/**
 * SolveVisitor class.
 *
 * for solve level
 */
class SolveVisitor : public Visitor
{
private:
    GameWord mWord;   ///< target word
    std::vector<std::shared_ptr<Letter>> mGivenTiles;  ///< given tiles
    std::vector<bool> mSolvedSlots; ///< tracks word position already filled

    int mTileWidth; ///< gets width
    int mTileHeight;  ///< gets height
    int mCurrentIndex = 0;  ///< get current index in word

public:
    /**
 * Constructor for SolveVisitor.
 *
 * Initializes the visitor with the game word, given tiles, and tile dimensions.
 *
 * @param word
 * @param givenTiles Letters that are already given
 * @param tileWidth Width
 * @param tileHeight Height
 */
    SolveVisitor(const GameWord& word, const std::vector<std::shared_ptr<Letter>>& givenTiles, int tileWidth, int tileHeight)
        : mWord(word), mGivenTiles(givenTiles), mTileWidth(tileWidth), mTileHeight(tileHeight)
    {
        mSolvedSlots.resize(word.GetLength(), false);

        // Mark slots that already have a given letter
        for (auto& given : givenTiles)
        {
            int col = given->GetX() / tileWidth;
            int row = given->GetY() / tileHeight;

            int index = col - mWord.GetStartCol();  // Convert col to index
            if (row == mWord.GetStartRow() && index >= 0 && index < mWord.GetLength())
            {
                mSolvedSlots[index] = true;
            }
        }
    }
    /**
     * Visit a movable letter and attempt to place it in correct positionn
     *
     * @param letter The movable letter to evaluate and place.
     */
    void VisitLetter(std::shared_ptr<Letter> letter) override
    {
        const auto& values = mWord.GetLetterValues();

        for (int i = 0; i < values.size(); ++i)
        {
            if (mSolvedSlots[i])
                continue; // Already filled by a Given

            if (letter->GetValue() == values[i])
            {
                int col = mWord.GetStartCol() + i;
                int row = mWord.GetStartRow();

                double x = col * mTileWidth;
                double y = row * mTileHeight;

                letter->SetLocation(x, y);
                mSolvedSlots[i] = true;
                break;
            }
        }
    }
};

#endif //BOGGLES_GAMELIB_SOLVEVISITOR_H
