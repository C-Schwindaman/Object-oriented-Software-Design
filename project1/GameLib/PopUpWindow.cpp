/**
 * @file PopUpWindow.cpp
 * @author Caleb Blackwell
 */

#include "pch.h"
#include "PopUpWindow.h"

/**
 * Constructor for the popup messages
 * @param frame
 */
PopUpWindow::PopUpWindow(wxWindow* frame) : wxFrame(frame, wxID_ANY, L"", wxDefaultPosition, wxSize(185, 200),
                                                    wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP | wxBORDER_NONE)
{
    if (frame != nullptr)
    {
        wxPoint parentPos = frame->GetPosition();
        wxSize parentSize = frame->GetSize();
        wxSize mySize = GetSize();

        int posX = parentPos.x + (parentSize.GetWidth() - mySize.GetWidth()) / 2;
        int posY = parentPos.y + (parentSize.GetHeight() - mySize.GetHeight()) / 2;

        SetPosition(wxPoint(posX, posY));
    }
}

/**
 * The initial message that pops up when the game/ levels first starts
 * @param message
 */
void PopUpWindow::Initialize(const wxString& message)
{
    auto panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxWHITE);

    auto panelSizer = new wxBoxSizer(wxVERTICAL);
    wxFont titleFont(64, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    auto titleText = new wxStaticText(panel, wxID_ANY, message);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(wxColour(0, 180, 0));

    wxFont instructionsFont(32, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    auto controlsText = new wxStaticText(panel, wxID_ANY, L"Spacebar: Grab\nA-Z,-: Release\nShift: Headbutt");
    controlsText->SetFont(instructionsFont);
    controlsText->SetForegroundColour(*wxBLACK);

    panelSizer->AddSpacer(10);
    panelSizer->Add(titleText, 0, wxALIGN_CENTER | wxALL, 10);
    panelSizer->AddSpacer(5);
    panelSizer->Add(controlsText, 0, wxALIGN_CENTER | wxALL, 10);
    panelSizer->AddSpacer(10);

    panel->SetSizer(panelSizer);
    panelSizer->Fit(panel);

    Fit();
    Show();

}

/**
 * Function to create the level complete message
 * @param message
 */
void PopUpWindow::LevelCompleteMessage(const wxString& message)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    wxFont titleFont(64, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    auto titleText = new wxStaticText(this, wxID_ANY, message);
    titleText->Wrap(500);

    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(wxColour(0, 180, 0));

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(titleText, 0, wxALIGN_CENTER | wxALL, 10);
    SetSizer(sizer);

    Fit();
    SetPosition(wxPoint(350, 350));
    Show();
}

/**
 * Function that builds the error message
 * @param message
 */
void PopUpWindow::ErrorMessage(const wxString& message)
{
    auto panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxBLACK);
    auto outerSizer = new wxBoxSizer(wxVERTICAL);

    this->Show();
    auto borderPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    borderPanel->SetBackgroundColour(*wxWHITE);
    auto innerSizer = new wxBoxSizer(wxVERTICAL);
    wxFont titleFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    auto titleText = new wxStaticText(borderPanel, wxID_ANY, message);
    titleText->SetFont(titleFont);

    titleText->SetForegroundColour(wxColour(180, 0, 0));
    innerSizer->Add(titleText, 0, wxALIGN_CENTER | wxALL, 10);
    borderPanel->SetSizer(innerSizer);
    outerSizer->Add(borderPanel, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(outerSizer);
    outerSizer->Fit(panel);
    Fit();

    wxSize screenSize = wxGetDisplaySize();
    wxSize frameSize = GetSize();
    int x = (screenSize.x - frameSize.x) / 2;
    int y = screenSize.y - frameSize.y - 50;
    SetPosition(wxPoint(x, y));

    this->Show();
}
