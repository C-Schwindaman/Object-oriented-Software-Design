/**
 * @file Scoreboard.cpp
 * @author Serena Brown
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Game.h"

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/**
 * Top-left corner of the scoreboard in virtual pixels.
 * @return none
 */
 const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Updates the scoreboard via elapsedtime and penalty time
 * @param elapsed
 */
void Scoreboard::Update(double elapsed) {
    mElapsedTime += elapsed;

    // Reduce the penalty time
    if (mPenaltyTime > 0)
    {
        mPenaltyTime -= elapsed;

        if (mPenaltyTime < 0)
        {
            mPenaltyTime = 0;
        }
    }
}

/**
 * Draws the scoreboard
 * @param gc
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> gc) {
    int minutes = static_cast<int>(mElapsedTime) / 60;
    int seconds = static_cast<int>(mElapsedTime) % 60;

    wxFont font(ScoreboardTextSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gc->SetFont(font, *wxWHITE);

    wxString timeText = wxString::Format("%02d:%02d", minutes, seconds);
    gc->DrawText(timeText, ScoreboardTopLeft.x, ScoreboardTopLeft.y);
    gc->SetPen(wxPen(*wxRED, 10));
    int strikes = mPenaltyStrikes;

    for (int i = 0; i < strikes; i++)
    {

        double startX = 50 + (i * 40);
        double startY = 550;
        double endY = startY + 150;

        gc->StrokeLine(startX, startY, startX, endY);
    }
}

/**
 * Resets the scoreboard to zero
 */
void Scoreboard::Reset() {
    mElapsedTime = 0.0;
    mPenaltyTime = 0.0;
    mPenaltyStrikes = 0;
}

/**
 * Adds 1 minute per strike
 */
void Scoreboard::AddPenaltyMinute()
{
    mPenaltyTime += 60.0;  // Add 60 seconds
    mElapsedTime += 60.0;
    mPenaltyStrikes++;
}
