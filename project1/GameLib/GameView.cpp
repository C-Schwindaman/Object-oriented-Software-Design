/**
* @file GameView.cpp
 * @author Caleb Blackwell, Serena Brown
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "GameView.h"
#include "ids.h"
#include "ItemVisitor.h"
#include "PopUpWindow.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Popup duration in milliseconds
const int PopupDuration = 5000;



/**
 * Initialize the game view with the given parent frame.
 * @param parent The parent wxFrame that will contain this panel.
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    Bind(wxEVT_TIMER, &GameView::OnRefresh, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_TIMER, &GameView::OnLevelTransition, this, ID_LEVEL_TRANSITION);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileSolve, this, IDM_SOLVE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpen, this, wxID_OPEN);
    Refresh();
    LoadLevel(mLevel);
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mPopupTimer.SetOwner(this);  // Start refresh timer to manage popups
    mPopupTimer.Start(FrameDuration);

    mLevelTransitionTimer.SetOwner(this, ID_LEVEL_TRANSITION);

    mStopWatch.Start();

    // Delay the popup slightly to ensure the window is fully drawn
    CallAfter([this]() { OnShowPopup(wxString::Format(L"Level 1 Begin")); });
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);

    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;



    // Only start updating the game (and scoreboard) after 3 seconds
    if (mStartScoreboard)
    {
        mGame.Update(elapsed);
    }

    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));
    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Loads the XML level file
 * @param event Command event object
 */
void GameView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Level File", L"levels", L"",
            L"XML Level Files (*.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxString filename = loadFileDialog.GetPath();
    mGame.LoadLevel(filename.ToStdString());
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event object
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());

    double clickX = event.GetX();
    double clickY = event.GetY();

    double gameX = (clickX - mGame.GetXOffset()) / mGame.GetScale();
    double gameY = (clickY - mGame.GetYOffset()) / mGame.GetScale();


    const GameWord& word = mGame.GetWord();

    int tileWidth = mGame.GetTileWidth();
    int tileHeight = mGame.GetTileHeight();

    for (int i = 0; i < word.GetLength(); ++i)
    {
        int col = word.GetStartCol() + i;
        int row = word.GetStartRow();

        double x = col * mGame.GetTileWidth();
        double y = row * mGame.GetTileHeight();

        if (gameX >= x && gameX <= x + mGame.GetTileWidth() && gameY >= y && gameY <= y + mGame.GetTileHeight())
        {
            mGame.SetSelectedIndex(i);
            return;
        }
    }

    mGame.ClearSelectedIndex();
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event object
 */
void GameView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event object
 */
void GameView::OnMouseMove(wxMouseEvent &event)
{
    if (mGrabbedItem != nullptr)
    {
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
            mGame.Update(0);
        }
        else
        {
            mGrabbedItem = nullptr;
        }

        Refresh();
    }
}

/**
 * Handle loading level before changing levels
 * @param level The current level
 */
void GameView::LoadLevel(int level)
{
    mLevel = level;
    wxString filename = wxString::Format(L"levels/level%d.xml", level);
    mGame.LoadLevel(filename.ToStdString());
    mGame.SetLevelThree(level == 3);
    // Reset the scoreboard when a new level is loaded
    mGame.ResetScoreboard();
    mStartScoreboard = false;

    OnShowPopup(wxString::Format(L"Level %d Begin", level));

    Refresh();
}

/**
 * Handle the key down event
 * @param event Key event object
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    int keyCode = event.GetKeyCode();

    ///get postition
    // wxPoint pos = event.GetPosition();


    //if space bar pressed
    if (keyCode == WXK_SPACE)
    {
        mGame.StartOpeningSequence();

        auto selectedLetter = mGame.GetSelectedLetter();
        if (!selectedLetter || !selectedLetter->IsLetter())
        {
            return;
        }

        if (mGame.IsTrayFull())
        {
            ShowErrorMessage(L"Max Capacity Reached!");
            return;
        }

        std::shared_ptr<Letter> letter = std::static_pointer_cast<Letter>(selectedLetter);
        ItemVisitor visitor(letter);
        letter->Accept(&visitor);

        auto collectedLetters = visitor.GetCollectedLetters();

        for (const auto& letterItem : collectedLetters)
        {
            mGame.MoveLetterToTray(letterItem);
        }

        mGame.ClearSelectedLetter();
    }
    else if (keyCode == WXK_SHIFT)
    {
        // Call the headbutt method in Game
        mGame.HeadbuttContainer();

    }

    else if ((keyCode >= 'A' && keyCode <= 'Z') || keyCode == '-')
    {

        int letterValue = (keyCode == '-') ? -20 : keyCode - 'A';

        int position = DetermineLetterPosition();


        if (mGame.IsLevelThree())
        {
            std::shared_ptr<Letter> letter = mGame.GetLetterFromTrayByValue(letterValue);

            if (letter && !mGame.IsCorrectLetter(letter, position))
            {

                mGame.AddPenaltyMinute();
                ShowErrorMessage(L"Wrong letter! +1 minute penalty");
            }
        }

        auto selectedLetter = mGame.GetSelectedLetter();
        if (selectedLetter && selectedLetter->IsLetter())
        {
            ShowErrorMessage(L"Something is already there!");
            return;
        }

        mGame.LetterFromTrayToWord(static_cast<char>(keyCode));
    }

    // Refresh
    Refresh();

    // Allow the event to skip
    event.Skip();
}

/**
 * Determines the position of the letter
 * @return Position of the letter
 */
int GameView::DetermineLetterPosition()
{
    // Get the player's current position
    wxPoint2DDouble playerPos = mGame.GetPlayerPosition();

    // Convert to grid coordinates
    int gridX = playerPos.m_x / mGame.GetTileWidth();
    int gridY = playerPos.m_y / mGame.GetTileHeight();

    // Calculate position index based on grid coordinates
    // This depends on your game's layout
    // For example, if you have a row-based position system:
    int position = gridY * mGame.GetGridWidth() + gridX;

    return position;
}

/**
 * Handle the timer event
 * @param event Timer event object
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Handle updates for animation
 * @param elapsedTime The time since the last update
 */
void GameView::Update(double elapsedTime)
{
    if (mActivePopup)
    {
        mPopupElapsedTime += elapsedTime;
        if (mPopupElapsedTime >= 3.0)
        {
            mActivePopup->Close();
            mActivePopup = nullptr;
            this->SetFocus();

            mStartScoreboard = true;

            // mGame.ResetScoreboard();

        } else if (mPopupMoving) {
            wxPoint pos = mActivePopup->GetPosition();
            mActivePopup->SetPosition(wxPoint(pos.x, pos.y - 7));
        }
    }
}

/**
 * Refreshes the timers with the elapsed time
 * @param event Timer event object
 */
void GameView::OnRefresh(wxTimerEvent& event)
{
    double newTime = mStopWatch.Time();
    double elapsed = (newTime - mTime) * 0.001;

    Update(elapsed);

    Refresh();
}

/**
 * Shows the popup at the start of the level
 * @param message Message shown in the popup
 */
void GameView::OnShowPopup(const wxString& message)
{
    if (mActivePopup)
    {
        mActivePopup->Close();
    }

    auto popup = new PopUpWindow(this);
    popup->Initialize(message);
    mActivePopup = popup;
    popup->Show();
    mPopupElapsedTime = 0.0;
    mPopupMoving = false;
}

/**
 * Completes the game when solved
 * @param event Command event object
 */
void GameView::OnFileSolve(wxCommandEvent& event){



    mGame.SolveLevel();
    Refresh();


    ShowLevelCompleteMessage();

    mLevelTransitionTimer.Start(3000, wxTIMER_ONE_SHOT);



}

/**
 * Shows the popup when the level is completed
 */
void GameView::ShowLevelCompleteMessage()
{
    if (mActivePopup)
    {
        mActivePopup->Close();
    }

    mActivePopup = new PopUpWindow(this);
    mActivePopup->LevelCompleteMessage(L"Level Complete!");
    mActivePopup->Show();
    mPopupElapsedTime = 0.0;
    mPopupMoving = false;
}

/**
 * Shows the popup when an error is encountered
 * @param message Message shown in the popup
 */
void GameView::ShowErrorMessage(const wxString message)
{
    if (mActivePopup)
    {
        mActivePopup->Close();
    }

    mActivePopup = new PopUpWindow(this);
    mActivePopup->ErrorMessage(message);
    mActivePopup->Show();
    mPopupElapsedTime = 0.0;
    mPopupMoving = true;
}

/**
 * Transitions game to next level
 * @param event Timer event object
 */
void GameView::OnLevelTransition(wxTimerEvent& event)
{
    if (mActivePopup)
    {
        mActivePopup->Close();
        mActivePopup = nullptr;
    }

    if (mLevel >= 3)
    {
        mLevel = 0;
    }
    else
    {
        mLevel++;
    }

    LoadLevel(mLevel);
    Refresh();
}


wxBEGIN_EVENT_TABLE(GameView, wxPanel)
        EVT_TIMER(GameView::ID_LEVEL_TRANSITION, GameView::OnLevelTransition)
wxEND_EVENT_TABLE()

