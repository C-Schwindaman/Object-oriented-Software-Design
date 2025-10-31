/**
 * @file Letter.cpp
 * @author Caleb Blackwell
 */

#include "pch.h"
#include "Letter.h"
#include <random>


/**
 * Constructor
 * @param game
 * @param c
 * @param r
 * @param w
 * @param h
 * @param filename
 * @param value
 */
Letter::Letter(Game* game, double c, double r, int w, int h, const std::wstring& filename, int value)
    : Item(game, filename), mColumn(c), mRow(r), mWidth(w), mHeight(h), mValue(value)
{
    mOriginalX = c * mWidth;
    mOriginalY = r * mHeight;

    mX = mTargetX = c * mWidth;
    mY = mTargetY = r * mHeight;

    mLetterValue = static_cast<char>(mValue + 'A');

    wxString path = L"images/" + filename;
    if (!mBitmap.LoadFile(path, wxBITMAP_TYPE_ANY))
    {
        std::wcout << L"Failed to load: " << path.ToStdWstring() << std::endl;
    }

}

/**
 * draws the letters on the screen
 * @param gc
 */
void Letter::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
    if (mBitmap.IsOk())
    {
        gc->DrawBitmap(mBitmap, mX, mY, mWidth, mHeight);
    }
}

/**
 * Updates the letter movement
 * @param elapsed
 */
void Letter::Update(double elapsed)
{
    const double speed = 200;

    if (mTargetX != mX || mTargetY != mY)
    {
        double deltaX = mTargetX - mX;
        double deltaY = mTargetY - mY;

        double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        if (distance < speed * elapsed)
        {
            mX = mTargetX;
            mY = mTargetY;
        }
        else
        {
            mX += (deltaX / distance) * speed * elapsed;
            mY += (deltaY / distance) * speed * elapsed;
        }
    }
}

/**
 * checks if a letter is being clicked
 * @param x
 * @param y
 * @return bool
 */
bool Letter::HitTest(int x, int y) const
{
    bool hit = (x >= mX && x <= mX + mWidth && y >= mY && y <= mY + mHeight);
    return hit;
}
