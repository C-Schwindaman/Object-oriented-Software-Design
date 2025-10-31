/**
 * @file Item.cpp
 * @author Caleb Blackwell
 */

#include "pch.h"
#include "Item.h"

using namespace std;

/**
 * Constructor
 * @param game
 * @param filename
 */
Item::Item(Game *game, const std::wstring &filename)
    : Item(game, filename, filename) {}  // Delegate to the main constructor

/**
 * constructor
 * @param game
 * @param filename
 * @param filename2
 */
Item::Item(Game *game, const std::wstring &filename, const std::wstring &filename2)
    : mGame(game)
{
    wxString path = L"images/" + filename;
    mItemImage = std::make_unique<wxImage>(path, wxBITMAP_TYPE_ANY);

    if (mItemImage && mItemImage->IsOk()) {
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    } else {
        std::cerr << "[ERROR] Failed to create wxBitmap: Invalid or missing image." << std::endl;
    }

    wxString path2 = L"images/" + filename2;
    mItemImage2 = std::make_unique<wxImage>(path2, wxBITMAP_TYPE_ANY);

    if (mItemImage2 && mItemImage2->IsOk()) {
        mItemBitmap2 = std::make_unique<wxBitmap>(*mItemImage2);
    } else {
        std::cerr << "[ERROR] Failed to create wxBitmap: Invalid or missing image." << std::endl;
    }
}

/**
* Draw this item
* @param gc Graphics context to draw on
*/
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc) {}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node) {}

/**
 * hittest
 * @param x
 * @param y
 * @return
 */
bool Item::HitTest(int x, int y) const
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        return false;
    }

    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/// destructor
Item::~Item()
{
}