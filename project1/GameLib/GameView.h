/**
* @file GameView.h
 * @author Caleb Blackwell
 *
 * Class that implements the child window our program draws in
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"
#include "PopUpWindow.h"

/**
 * Class that implements the child window our program draws in
 */
class GameView  : public wxPanel {
private:
    /// An object that describes our game
    Game mGame;
    /// Any item we are currently grabbing
    std::shared_ptr<Item> mGrabbedItem;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Elapsed time the popup has been shown
    double mPopupElapsedTime = 0.0;
    /// The timer for the displayed popup
    wxTimer mPopupTimer;
    /// A pointer to the active popup
    PopUpWindow *mActivePopup = nullptr;
    /// The timer for the level transition
    wxTimer mLevelTransitionTimer;
    /// The ID for the level transition
    static const int ID_LEVEL_TRANSITION = wxID_HIGHEST + 1;
    /// A pointer to the selected letter
    std::shared_ptr<Item> mSelectedLetter;
    /// Is the popup moving?
    bool mPopupMoving = false;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;
    /// The current level of the game
    int mLevel = 1;
    /// Has the scoreboard started?
    bool mStartScoreboard = false;

public:
    void Initialize(wxFrame* parent);
    void LoadLevel(int level);
    void OnPaint(wxPaintEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxTimerEvent& event);
    void Update(double elapsedTime);
    void OnRefresh(wxTimerEvent& event);
    void OnShowPopup(const wxString& message);
    void OnFileSolve(wxCommandEvent &event);
    /**
     * Declares the event table for GameView to handle events such as timers and mouse input.
     */
    wxDECLARE_EVENT_TABLE();
    void OnLevelTransition(wxTimerEvent &event);
    void ShowLevelCompleteMessage();
    void ShowErrorMessage(wxString message);
    int DetermineLetterPosition();
};


#endif //GAMEVIEW_H
