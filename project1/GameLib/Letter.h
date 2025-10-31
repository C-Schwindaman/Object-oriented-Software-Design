/**
 * @file Letter.h
 * @author Caleb Blackwell
 *
 * A class for letter items
 */
 
#ifndef LETTER_H
#define LETTER_H

#include "Item.h"
#include "Visitor.h"

/**
 * A class for letter items
 */
class Letter : public Item, public std::enable_shared_from_this<Letter> {
private:

protected:
    /// Column position
    double mColumn;
    /// Row position
    double mRow;
    /// Width of the Letter
    int mWidth;
    /// Height of the Letter
    int mHeight;
    /// Value of the Letter
    int mValue;
    /// Value of the Letter
    char mLetterValue;
    /// Bitmap of the Letter
    wxBitmap mBitmap;
    /// x variable
    double mX;
    /// y variable
    double mY;
    /// x target variable
    double mTargetX = mX;
    /// y target variable
    double mTargetY = mY;
    /// x original variable
    double mOriginalX;
    /// y original variable
    double mOriginalY;
    /// returns if letter is in the original position from xml
    bool mIsOriginalPositionSet = false;

public:
    /// Default constructor (disabled)
    Letter() = delete;

    /// Copy constructor (disabled)
    Letter(const Letter &) = delete;

    /// Assignment operator
    void operator=(const Letter &) = delete;

    Letter(Game* game, double c, double r, int w, int h, const std::wstring& filename, int value);
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void Update(double elapsed) override;
    bool HitTest(int x, int y) const override;

    /**
     * Visitor class for letter
     * @param visitor
     */
    virtual void Accept(Visitor* visitor) override
    {
        visitor->VisitLetter(shared_from_this());
    }

    /**
     * returns the value of letter
     * @return mValue
     */
    int GetValue() const override { return mValue; }

    /**
     * returns the letter value (char specifically)
     * @return mLetterValue
     */
    char GetLetterValue() const override { return mLetterValue; }

    /**
     * Sets the location of letter
     * @param x
     * @param y
     */
    void SetLocation(double x, double y)
    {
        mX = mTargetX = x;
        mY = mTargetY = y;
    }

    /**
     * gets the x variable of letter
     * @return mX
     */
    double GetX() const { return mX; }

    /**
     * gets the y variable of letter
     * @return mY
     */
    double GetY() const { return mY; }

    /**
     * gets the original location of x
     * @return mOriginalX
     */
    double GetOriginalX() const override
    {
        return mOriginalX;
    }

    /**
     * gets the original location of y
     * @return mOriginalY
     */
    double GetOriginalY() const override
    {
        return mOriginalY;
    }

    /**
     * gets the width of letter
     * @return mWidth
     */
    double GetWidth() const override { return mWidth; }

    /**
     * gets the height of letter
     * @return mHeight
     */
    double GetHeight() const override { return mHeight; }

    /**
     * returns if clicked object is a letter
     * @return bool
     */
    bool IsLetter() const override {return true;}

    /**
     * returns if clicked object is the container
     * @return bool
     */
    bool IsContainer() const override { return false; }

    /**
     * resets the position of letter
     */
    void ResetPosition() override { SetLocation(200, 200); }
};



#endif //LETTER_H
