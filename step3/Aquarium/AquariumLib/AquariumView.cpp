/**
 * @file AquariumView.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include "AquariumView.h"
#include "ids.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include "FishAngel.h"
#include "FishFinfluencer.h"

using namespace std;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_LEFT_DCLICK, &AquariumView::OnMouseDoubleClick, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishNemo, this, IDM_ADDFISHNEMO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishAngelFish, this, IDM_ADDFISHANGEL);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishFinfluencerFish, this, IDM_ADDFISHFINFLUENCER);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mAquarium.OnDraw(&dc);
}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Nemo
 * @param event Mouse event
 */
void AquariumView::OnAddFishNemo(wxCommandEvent& event)
{
    auto fish = make_shared<FishNemo>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Angel Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishAngelFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishAngel>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu hander for Add Fish>Angel Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishFinfluencerFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishFinfluencer>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem)
    {
        mAquarium.MoveToEnd(mGrabbedItem);
        mGrabbedItem->Deactive();
        Refresh();
    }
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handle the mouse double click event
 * @param event
 */
void AquariumView::OnMouseDoubleClick(wxMouseEvent& event)
{
    auto fish = mAquarium.HitTest(event.GetX(), event.GetY());
    if (fish)
    {
        fish->Active();
        mAquarium.MoveItems(fish);
        Refresh();
    }
}