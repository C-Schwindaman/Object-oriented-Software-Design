/**
 * @file Given.h
 * @author Meghan Carter
 *
 *
 */
 
#ifndef GIVEN_H
#define GIVEN_H

#include "Item.h"

/**
* Class representing a given tile in the game
* This class derives from tile and represents a given tile in the game
*/
class Given : public Item {
private:

public:
  /// Default constructor (disabled)
  Given() = delete;

  /// Copy constructor (disabled)
  Given(const Given &) = delete;

  /// Assignment operator
  void operator=(const Given &) = delete;

  /// Constructor with parameters
  Given(Game* game, int c, int r, int w, int h, const std::wstring& filename, int value);

  /// Override IsMovable to prevent moving the tile
  bool IsMovable() const override;

  /**
   * Get the value of the given
   * @return The value of the given
   */
  int GetValue() const override { return mValue; }

protected:
  /// Value of the Given
  int mValue;
  /// Column position
  double mColumn;
  /// Row position
  double mRow;
  /// Width of the Given
  int mWidth;
  /// Height of the Given
  int mHeight;


};



#endif //GIVEN_H
