/**
 * @file ItemVisitor.h
 * @author Serena
 *
 *
 */

#ifndef BOGGLES_GAMELIB_ITEMVISITOR_H
#define BOGGLES_GAMELIB_ITEMVISITOR_H

#include "Visitor.h"
#include "Letter.h"
#include <vector>

/**
 * Item Visitor class and subclass from Visitor
 */
class ItemVisitor : public Visitor
{
private:
    /// number of letters collected
    int mNumCollectedLetters = 0;
    /// target letter being clicked
    std::shared_ptr<Letter> mTargetLetter;
    /// vector of collected letters
    std::vector<std::shared_ptr<Letter>> mCollectedLetters;
public:
    /**
     * Constructor
     * @param letter
     */
    ItemVisitor(std::shared_ptr<Letter> letter) : mTargetLetter(letter) {}

    /**
     * function that visits the letter class
     * @param letter
     */
    void VisitLetter(std::shared_ptr<Letter> letter) override
    {
        if (letter == mTargetLetter)
        {
            mCollectedLetters.push_back(letter);
            mNumCollectedLetters++;
        }
    }

    /**
     * returns the number of collected letters in tray
     * @return mNumCollectedLetters
     */
    int GetNumCollected() const {return mNumCollectedLetters;}

    /**
     * the letters that are collected in the tray
     * @return mCollectedLetters
     */
    const std::vector<std::shared_ptr<Letter>>& GetCollectedLetters() const {return mCollectedLetters;}

};

#endif //BOGGLES_GAMELIB_ITEMVISITOR_H
