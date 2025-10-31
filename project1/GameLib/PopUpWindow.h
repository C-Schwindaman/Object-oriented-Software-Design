/**
 * @file PopUpWindow.h
 * @author Caleb Blackwell
 *
 *
 */
 
#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <wx/popupwin.h>

/**
 * Class that creates the messages within the game. Taken from wxFrame for formatting
 */
class PopUpWindow : public wxFrame {
private:

public:
    /// Default constructor (disabled)
    PopUpWindow() = delete;

    /// Copy constructor (disabled)
    PopUpWindow(const PopUpWindow &) = delete;

    /// Assignment operator
    void operator=(const PopUpWindow &) = delete;

    PopUpWindow(wxWindow *frame);
    void Initialize(const wxString& message);
    void LevelCompleteMessage(const wxString& message);
    void ErrorMessage(const wxString& message);
};



#endif //POPUPWINDOW_H
