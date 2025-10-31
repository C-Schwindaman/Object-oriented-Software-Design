/**
* @file GameWord.h
 * @author Meghan Carter
 */

#ifndef GAMEWORD_H
#define GAMEWORD_H

#include <vector>

/**
 * Class representing a word placed in game
 * Stores its starting position
 */
class GameWord
{
private:
    /// Column where the word starts
    int mStartCol = 0;
    /// Row where the word starts
    int mStartRow = 0;
    /// Length of the word
    int mLength = 0;
    /// Numeric values representing the letters of the word
    std::vector<int> mLetterValues;

public:
    /// Default constructor
    GameWord() = default;

    /**
     * Constructor
     * @param col Starting column of word
     * @param row Starting row of word
     * @param length  Length of word
     * @param values Vector of letter values
     */
    GameWord(int col, int row, int length, const std::vector<int>& values)
        : mStartCol(col), mStartRow(row), mLength(length), mLetterValues(values)
    {}

    /**
     * Get the starting column of word
     * @return  Starting column index
     */
    int GetStartCol() const { return mStartCol; }

    /**
     * Get the starting row of word
     * @return Starting row index
     */
    int GetStartRow() const { return mStartRow; }

    /**
     * Get the length of word
     * @return Length of the word
     */
    int GetLength() const { return mLength; }

    /**
     * Get the letter values of word
     * @return Const reference to a vector of letter values
     */
    const std::vector<int>& GetLetterValues() const { return mLetterValues; }

    /**
     * Set the starting column of the word
     * @param col Column index to set
     */
    void SetStartCol(int col) { mStartCol = col; }

    /**
     * Set the starting row of the word
     * @param row Row index to set
     */
    void SetStartRow(int row) { mStartRow = row; }

    /**
     * Set the length of word
     * @param length New length to set
     */
    void SetLength(int length) { mLength = length; }

    /**
     * Set the letter values of word
     * @param values Vector of new letter values
     */
    void SetLetterValues(const std::vector<int>& values) { mLetterValues = values; }
};

#endif
