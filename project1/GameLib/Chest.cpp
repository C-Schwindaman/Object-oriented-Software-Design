/**
 * @file Chest.cpp
 * @author Meghan Carter
 */

#include "pch.h"
#include "Chest.h"

/**
 * Constructor
 * @param game The game this Chest belongs to
 * @param c Column position
 * @param r Row position
 * @param w Width of the Chest
 * @param h Height of the Chest
 * @param filename Filename of image1
 * @param tileHeight Height of the tiles in game
 * @param filename2 Filename of image2
 * @param mPA Mouth pivot angle
 * @param mPX Mouth pivot X
 * @param mPY Mouth pivot Y
 */
Chest::Chest(Game* game, double c, double r, int w, int h, const std::wstring& filename, int tileHeight, const std::wstring& filename2, double mPA, int mPX, int mPY)
    : Player(game, c, r, w, h, filename, tileHeight, filename2, mPA, mPX, mPY)
{
}