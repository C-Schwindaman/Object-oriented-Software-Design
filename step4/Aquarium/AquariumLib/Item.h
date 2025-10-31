/**
 * @file Item.h
 * @author Cameron Schwindaman
 *
 * Base class for any item in our aquarium.
 */

#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

#include <wx/xml/xml.h>

class Aquarium;

/**
 * Base class for any item in our aquarium.
 */
class Item {
private:
    /// The aquarium this item is contained in
    Aquarium   *mAquarium;

    /// Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    bool mMirror = false;   ///< True mirrors the item image

public:
    virtual ~Item();
    bool HitTest(int x, int y);
    void Draw(wxDC *dc);
    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);
    void SetMirror(bool m);

    /**
     * The X location of the item
     * @return X location in pixe
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium *GetAquarium() { return mAquarium;  }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Get the width of the item
     * @return Item width in pixels
     */
    int GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * Get the height of the item
     * @return Item height in pixels
     */
    int GetHeight() const { return mItemBitmap->GetHeight(); }

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

protected:
    Item(Aquarium* aquarium, const std::wstring& filename);
};

#endif //AQUARIUM_ITEM_H