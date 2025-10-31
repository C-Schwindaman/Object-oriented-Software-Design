/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>
#include "ViewTimeline.h"
#include "Picture.h"
#include "TimelineDlg.h"
#include "Timeline.h"
#include "Actor.h"

using namespace std;

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir Directory within the resources that contains the images
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
             &ViewTimeline::OnEditTimelineProperties, this,
             XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));

    mPointerImage = make_unique<wxImage>(imagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetPicture()->GetSize();
    SetVirtualSize(size.GetWidth(), size.GetHeight());
    SetScrollRate(1, 0);

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 0, 0), 1);
    graphics->SetPen(pen);

    wxFont font(wxSize(0, 16),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    Timeline* timeline = GetPicture()->GetTimeline();
    for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); ++tickNum)
    {
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;

        int x1 = BorderLeft + (TickSpacing * tickNum);
        int x2 = BorderRight + (TickSpacing * tickNum);
        int y1 = TickTop;
        int y2 = TickShort;

        graphics->StrokeLine(x1, y1, x2, y2);

        if(onSecond)
        {
            y2 = TickLong;
            graphics->StrokeLine(x1, y1, x2, y2);

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);

            double textX = x1 - (w / 2);
            double textY = y2 + TickSpacing;

            graphics->DrawText(wstr, textX, textY);
        }
    }

    mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);

    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    graphics->DrawBitmap(mPointerBitmap, pointerX - mPointerImage->GetWidth()/2, mPointerImage->GetHeight()/2,
        mPointerImage->GetWidth(), mPointerImage->GetHeight());
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    if (event.LeftIsDown() && mMovingPointer) {
        auto click = CalcUnscrolledPosition(event.GetPosition());
        double x = click.x;

        Timeline* timeline = GetPicture()->GetTimeline();
        double newTime = (x - BorderLeft) / (timeline->GetFrameRate() * TickSpacing);

        if (newTime < 0) {
            newTime = 0;
        } else if (newTime > timeline->GetDuration()) {
            newTime = timeline->GetDuration();
        }

        GetPicture()->SetAnimationTime(newTime);
        UpdateObserver();

    } else {
        mMovingPointer = false;
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Tmeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Handle an Edit>Set Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Handle an Edit>Delete Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->DeleteKeyframe();
    }
    picture->SetAnimationTime(picture->GetTimeline()->GetCurrentTime());
}
