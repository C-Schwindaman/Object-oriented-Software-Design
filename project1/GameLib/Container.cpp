/**
 * @file Container.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <random>
#include "Container.h"
#include "Letter.h"

/**
 * Constructor
 * @param game The game this Container belongs to
 * @param filename Filename of image
 * @param filename2 Filename of front
 */
Container::Container(Game* game, const std::wstring &filename, const std::wstring &filename2) : Item(game, filename)

{
    std::wstring basePath = L"images/" + filename;
    std::wstring frontPath = L"images/" + filename2;

    mBaseImage = std::make_unique<wxImage>(basePath, wxBITMAP_TYPE_ANY);
    mFrontImage = std::make_unique<wxImage>(frontPath, wxBITMAP_TYPE_ANY);

    mBaseBitmap = std::make_unique<wxBitmap>(*mBaseImage);
    mFrontBitmap = std::make_unique<wxBitmap>(*mFrontImage);
}

/**
 * Draw the container
 * @param graphics The graphics context to draw on
 */
void Container::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
}

void Container::Accept(Visitor* visitor)
{
    visitor->VisitContainer(this);
}

bool Container::Headbutt()
{
    if (mLetters.empty() || mHeadbutted)
    {
        return false;
    }

    ReleaseLetters();
    mHeadbutted = true;
    return true;
}

void Container::AddLetter(std::shared_ptr<Letter> letter)
{
    mLetters.push_back(letter);
}

void Container::ReleaseLetters()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> xDist(-150.0, 150.0);
    std::uniform_real_distribution<> yDist(-200.0, -50.0);

    double x = GetX();
    double y = GetY();

    for (auto& letter : mLetters)
    {
        double offsetX = xDist(gen);
        double offsetY = yDist(gen);
        letter->SetLocation(x + offsetX, y + offsetY);

        // Add the letter back to the game's item list
        GetGame()->AddItem(letter);
    }

    mLetters.clear();
}