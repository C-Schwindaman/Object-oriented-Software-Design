/**
 * @file Item.h
 * @author Caleb Blackwell
 *
 * Base class for any item inside our game
 */
 
#ifndef ITEM_H
#define ITEM_H

#include <wx/xml/xml.h>

/**
 * forward reference of game
 */
class Game;

/**
 * forward reference of visitor
 */
class Visitor;

/**
 * Base class for any item inside our game
 */
class Item {
private:
    /// The game that the item is contained inside
    Game *mGame;
    /// width of item
    double mWidth = 0;
    /// height of item
    double mHeight = 0;
    /// The underlying image
    std::unique_ptr<wxImage> mItemImage;
    /// The bitmap we can display for the item
    std::unique_ptr<wxBitmap> mItemBitmap;
    /// The underlying image
    std::unique_ptr<wxImage> mItemImage2;
    /// The bitmap we can display for the item
    std::unique_ptr<wxBitmap> mItemBitmap2;
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
    /// original x of item
    const double mOriginalX = 0;
    /// original y of item
    const double mOriginalY = 0;
protected:
    Item(Game* game, const std::wstring& filename);
    Item(Game* game, const std::wstring& filename, const std::wstring& filename2);

public:
    /**
    * Destructor
    */
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);
    virtual bool HitTest(int x, int y) const;

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * gets the original x
     * @return 0
     */
    virtual double GetOriginalX() const { return 0; }

    /**
     * gets the original y
     * @return 0
     */
    virtual double GetOriginalY() const { return 0; }

    /**
     * Check if the item is movable
     * @return True if movable, false otherwise
     */
    virtual bool IsMovable() const {return true; }

    /**
     * Accept a visitor
      * @param visitor The visitor we accept
      */
    virtual void Accept(Visitor* visitor) = 0;

    /**
     * if item is a letter
     * @return bool
     */
    virtual bool IsLetter() const {return false;}

    /**
     * if item is the tray
     * @return bool
     */
    virtual bool IsTray() const {return false;}

    /**
     * returns if able to add a letter
     * @param letter
     * @return bool
     */
    virtual bool AddLetter(std::shared_ptr<Item> letter) {return false;};

    /**
     * gets the value of a letter
     * @return int
     */
    virtual int GetValue() const { return -1; }

    /**
     * gets the value of a letter (char)
     * @return char
     */
    virtual char GetLetterValue() const { return -1; }

    /**
     * gets the width of item
     * @return double
     */
    virtual double GetWidth() const { return mWidth; }

    /**
     * gets the height of item
     * @return double
     */
    virtual double GetHeight() const { return mHeight; }

    /**
     * returns if item is the container
     * @return bool
     */
    virtual bool IsContainer() const { return false; }

    /**
     * gets the game
     * @return mGame
     */
    Game* GetGame() const { return mGame; }

    /**
     * resets the position of item
     */
    virtual void ResetPosition() {}
};



#endif //ITEM_H
