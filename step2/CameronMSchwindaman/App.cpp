/**
 * @file App.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <MainFrame.h>
#include "App.h"

/**
 * Initialize the application.
 * @return
 */
bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}