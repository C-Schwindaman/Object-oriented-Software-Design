/**
 * @file Player.h
 * @author Caleb Blackwell
 *
 * Class player as a subclass of item.
 */
 
#ifndef PLAYER_H
#define PLAYER_H
#include "Item.h"
#include "Visitor.h"

class Game;

/**
 * Class player as a subclass of item.
 * In charge of player movement and animation.
 */
class Player : public Item {
private:
    /// member variable set to game
    Game* mGame;
    /// Player speed in the X direction
    double mSpeedX;
    /// Player speed in the Y direction
    double mSpeedY;
    /// The current location of the player
    wxPoint2DDouble mLocation;
    /// Where we want the player to go
    wxPoint2DDouble mTarget;
    /// Current rotation angle
    double mMouthAngle;
    /// Maximum rotation angle from XML (mouth-pivot-angle)
    double mTargetAngle;
    /// Rotation pivot point
    wxPoint mMouthPivot;
    /// to check if sparty is animating
    bool mAnimating = false;
    /// to check if chest is opening
    bool mOpening = true;
    /// to check if player is chest
    bool mIsChest = true;
protected:
    /// the space where player spawns in based on the level xml information via column (x)
    double mColumn;
    /// the space where player spawns in based on the level xml information via row (y)
    double mRow;
    /// the width of the player via level xml
    int mWidth;
    /// the height of the player via level xml
    int mHeight;
    /// member variable for bitmap
    wxBitmap mBitmap;
    /// the member variable for the secondary bitmap
    wxBitmap mSecondaryBitmap;

public:
    /// Default constructor (disabled)
    Player() = delete;

    /// Copy constructor (disabled)
    Player(const Player &) = delete;

    /// Assignment operator
    void operator=(const Player &) = delete;

    void Update(double elapsed) override;
    Player(Game* game, double c, double r, int w, int h, const std::wstring& filename, int tileHeight,
           const std::wstring& filename2, double mPA, int mPX, int mPY,  bool isChest = true);
    void Draw(std::shared_ptr<wxGraphicsContext> gc) override;
    void SetPlayerLocation(int x, int y);
    void StartOpening();

    /**
     * Accept a visitor
     * @param visitor The visitor to accept
     */
    void Accept(Visitor* visitor) override {
        visitor->VisitPlayer(this);
    }
};



#endif //PLAYER_H
