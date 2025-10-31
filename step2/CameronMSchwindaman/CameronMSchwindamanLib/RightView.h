/**
 * @file RightView.h
 * @author Cameron Schwindaman
 *
 * Right view class for our application
 */
 
#ifndef CAMERONMSCHWINDAMAN_RIGHTVIEW_H
#define CAMERONMSCHWINDAMAN_RIGHTVIEW_H

/**
 * Right view class for our application
 */
class RightView : public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);
};

#endif //CAMERONMSCHWINDAMAN_RIGHTVIEW_H
