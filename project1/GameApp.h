/**
 * @file GameApp.h
 * @author Serena Brown
 *
 *
 */

#ifndef BOGGLES__GAMEAPP_H
#define BOGGLES__GAMEAPP_H

#include <wx/wx.h>

/**
 * Main application class
 */
class GameApp : public wxApp {
public:
    bool OnInit() override;

};

#endif //BOGGLES__GAMEAPP_H
