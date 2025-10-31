/**
 * @file Given.cpp
 * @author Meghan Carter
 */

#include "pch.h"
#include "Given.h"

/**
 * Constructor
 * @param game The game this tile belongs to.
 * @param c Column position.
 * @param r Row position.
 * @param w Width of the tile.
 * @param h Height of the tile.
 * @param filename The image file for this tile.
 * @param value The value of the tile.
 */
Given::Given(Game* game, int c, int r, int w, int h, const std::wstring& filename, int value) : Item(game, filename), mColumn(c), mRow(r), mWidth(w), mHeight(h)
{}

/**
 * Check if the tile is movable.
 * @return False since given tiles cannot be moved.
 */
bool Given::IsMovable() const {
  return false;
  }



