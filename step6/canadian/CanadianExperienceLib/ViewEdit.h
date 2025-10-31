/**
 * @file ViewEdit.h
 * @author Charles B. Owen
 * @author Cameron Schwindaman
 *
 * Basic edit view class for the Canadian Experience
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#ifndef CANADIANEXPERIENCE_VIEWEDIT_H
#define CANADIANEXPERIENCE_VIEWEDIT_H

#include "Drawable.h"
#include "PictureObserver.h"

class Actor;

/**
 * Basic edit view class for the Canadian Experience
 */
class ViewEdit final : public wxScrolledCanvas, public PictureObserver {
private:
    /// The current mouse mode
    enum class Mode {Move, Rotate};

    /// The currently set mouse mode
    Mode mMode = Mode::Move;

    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// The selected drawable of this view
    std::shared_ptr<Drawable> mSelectedDrawable;

    /// The selected actor of this view
    std::shared_ptr<Actor> mSelectedActor;

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

public:
    ViewEdit(wxFrame* parent);
    void UpdateObserver() override;
    void OnEditMove(wxCommandEvent& event);
    void OnEditRotate(wxCommandEvent& event);
    void OnUpdateEditMove(wxUpdateUIEvent& event);
    void OnUpdateEditRotate(wxUpdateUIEvent& event);
};

#endif //CANADIANEXPERIENCE_VIEWEDIT_H
