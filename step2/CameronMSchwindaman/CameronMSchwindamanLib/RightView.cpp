/**
 * @file RightView.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include "RightView.h"

/**
 * Initialize the right view class.
 * @param parent The parent window for this class
 */
void RightView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &RightView::OnPaint, this);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void RightView::OnPaint(wxPaintEvent& event)
{
    // Add white background
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Draw red sections of fish
    wxBrush brush(wxColour(153, 0, 0));
    dc.SetBrush(brush);
    dc.DrawRectangle(268, 184, 252, 252);
    dc.DrawRectangle(310, 142, 84, 43);
    dc.DrawRectangle(352, 435, 126, 42);
    dc.DrawRectangle(184, 268, 85, 84);

    // Draw white sections of top fin
    brush = (wxColour(0, 0, 0));
    dc.SetBrush(brush);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(310, 100, 84, 43);
    dc.DrawRectangle(393, 142, 84, 43);

    // Draw white sections of fish body
    brush = (wxColour(255, 255, 255));
    dc.SetBrush(brush);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(268, 226, 42, 42);
    dc.DrawRectangle(310, 184, 42, 42);
    dc.DrawRectangle(310, 268, 84, 84);
    dc.DrawRectangle(268, 352, 42, 84);
    dc.DrawRectangle(436, 310, 84, 42);
    dc.DrawRectangle(478, 268, 42, 42);
    dc.DrawRectangle(352, 352, 42, 42);

    // Draw black eye
    brush = (wxColour(0, 0, 0));
    dc.SetBrush(brush);
    dc.DrawRectangle(394, 310, 42, 42);

    // Draw outline of fish body
    wxPen pen(wxColour(0, 0, 0), 1);
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(268, 184, 252, 252);

    // Draw white sections of the fins
    dc.DrawLine(184, 268, 142, 268);
    dc.DrawLine(142, 268, 142, 226);
    dc.DrawLine(142, 226, 100, 226);
    dc.DrawLine(100, 226, 100, 184);
    dc.DrawLine(100, 184, 184, 184);
    dc.DrawLine(184, 184, 184, 226);
    dc.DrawLine(184, 226, 268, 226);

    dc.DrawLine(184, 351, 142, 351);
    dc.DrawLine(142, 351, 142, 393);
    dc.DrawLine(142, 393, 100, 393);
    dc.DrawLine(100, 393, 100, 435);
    dc.DrawLine(100, 435, 184, 435);
    dc.DrawLine(184, 435, 184, 393);
    dc.DrawLine(184, 393, 268, 393);

    dc.DrawLine(310, 435, 310, 519);
    dc.DrawLine(310, 519, 436, 519);
    dc.DrawLine(436, 519, 436, 477);

    // Draw bubbles
    wxPen pen2(wxColour(0, 255, 255), 3);
    dc.SetPen(pen2);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(550, 300, 21);
    dc.DrawCircle(630, 225, 42);
    dc.DrawCircle(575, 100, 84);

    brush = (wxColour(0, 255, 255));
    dc.SetBrush(brush);
    dc.DrawCircle(560, 290, 1);
    dc.DrawCircle(605, 210, 5);
    dc.DrawCircle(620, 75, 15);
}