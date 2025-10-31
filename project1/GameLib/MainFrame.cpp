/**
 * @file MainFrame.cpp
 * @author Serena Brown, Caleb Blackwell
 */


#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "GameView.h"


using namespace std;
/**
* Initialize the MainFrame window.
*/
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Spartanmind", wxDefaultPosition,  wxSize( 950,750 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Set the sizer for this frame
    SetSizer( sizer );

    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    // Layout (place) the child windows.
    Layout();
    auto menuBar = new wxMenuBar( );
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();


    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar( menuBar );

    fileMenu->Append(IDM_SOLVE, "&Solve");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X"); // fileMenu should solve


    helpMenu->Append(wxID_ABOUT, "&About\tF1");
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::Help, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);


    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Level 3");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelSelected, this, IDM_LEVEL0);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelSelected, this, IDM_LEVEL1);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelSelected, this, IDM_LEVEL2);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelSelected, this, IDM_LEVEL3);


}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Help menu option message box
 * @param event
 */
void MainFrame::Help(wxCommandEvent& event)
{

    wxMessageBox(L"Welcome to Spartanmind",
                 L" -Team Boggle",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    if (mGameView != nullptr)
    {
        delete mGameView;
        mGameView = nullptr;
    }
    Destroy();
}

/**
 * Handle a level selected event. Automatically change to level selected.
 * @param event
 */
void MainFrame::OnLevelSelected(wxCommandEvent& event)
{
    int level = -1;

    switch (event.GetId())
    {
    case IDM_LEVEL0:
        level = 0;
        break;
    case IDM_LEVEL1:
        level = 1;
        break;
    case IDM_LEVEL2:
        level = 2;
        break;
    case IDM_LEVEL3:
        level = 3;
        break;
    }

    if (level >= 0)
    {
        mGameView->LoadLevel(level);
    }
    else
    {
        wxMessageBox("mGameView is null or invalid level selected.", "Debug Error", wxOK | wxICON_ERROR);
    }
}
