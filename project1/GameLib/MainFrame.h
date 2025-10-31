/**
 * @file MainFrame.h
 * @author Serena Brown
 *
 * Sets up the frame of the game using wxFrame to help build
 */

#ifndef BOGGLES_GAMELIB_MAINFRAME_H
#define BOGGLES_GAMELIB_MAINFRAME_H

#include <wx/event.h>
#include "GameView.h"

/**
 * Sets up the frame of the game using wxFrame to help build
 */
class MainFrame : public wxFrame {
private:
    /// member variable for GameView
    GameView* mGameView = nullptr;

public:
    void Initialize();
    void OnExit(wxCommandEvent &event);
    void Help(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
    void OnLevelSelected(wxCommandEvent& event);
};

#endif //BOGGLES_GAMELIB_MAINFRAME_H
