/**
 * @file AquariumApp.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <MainFrame.h>
#include "AquariumApp.h"

/**
 * Initialize the application.
 * @return
 */
bool AquariumApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}