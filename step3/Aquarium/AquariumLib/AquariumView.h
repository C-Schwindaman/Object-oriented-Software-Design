/**
 * @file AquariumView.h
 * @author Cameron Schwindaman
 *
 * View class for our aquarium
 */
 
#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H

#include "Aquarium.h"

/**
 * View class for our aquarium
 */
class AquariumView : public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);

    /// An object that describes our aquarium
    Aquarium  mAquarium;

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

public:
    void Initialize(wxFrame* parent);
    void OnAddFishBetaFish(wxCommandEvent& event);
    void OnAddFishNemo(wxCommandEvent& event);
    void OnAddFishAngelFish(wxCommandEvent& event);
    void OnAddFishFinfluencerFish(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseDoubleClick(wxMouseEvent& event);
};

#endif //AQUARIUM_AQUARIUMVIEW_H
