/**
 * @file SpartyFactory.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace std;

/**
 * This is a factory method that creates our Harold actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> SpartyFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Harold");

    auto torso = make_shared<ImageDrawable>(L"Torso", imagesDir + L"/sparty_torso.png");
    torso->SetCenter(wxPoint(73, 108));
    torso->SetPosition(wxPoint(0, 0));
    actor->SetRoot(torso);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/sparty_lleg.png");
    lleg->SetCenter(wxPoint(40, 22));
    lleg->SetPosition(wxPoint(35, 90));
    torso->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/sparty_rleg.png");
    rleg->SetCenter(wxPoint(36, 22));
    rleg->SetPosition(wxPoint(-35, 90));
    torso->AddChild(rleg);

    auto headb = make_shared<ImageDrawable>(L"Head Bottom", imagesDir + L"/sparty_lhead.png");
    headb->SetCenter(wxPoint(56, 36));
    headb->SetPosition(wxPoint(0, -75));
    torso->AddChild(headb);

    auto headt = make_shared<HeadTop>(L"Head Top", imagesDir + L"/sparty_head.png");
    headt->SetCenter(wxPoint(52, 142));
    headt->SetPosition(wxPoint(0, -30));
    headt->SetLeftEye(wxPoint(35, 113));
    headt->SetRightEye(wxPoint(70, 113));
    headt->SetStartLeftEyebrow(wxPoint(22, 105));
    headt->SetStartRightEyebrow(wxPoint(75, 98));
    headt->SetEndLeftEyebrow(wxPoint(30, 98));
    headt->SetEndRightEyebrow(wxPoint(84, 105));
    headb->AddChild(headt);

    auto larm = make_shared<ImageDrawable>(L"Left Arm", imagesDir + L"/sparty_larm.png");
    larm->SetCenter(wxPoint(22, 20));
    larm->SetPosition(wxPoint(55, -80));
    torso->AddChild(larm);

    auto rarm = make_shared<ImageDrawable>(L"Right Arm", imagesDir + L"/sparty_rarm.png");
    rarm->SetCenter(wxPoint(96, 20));
    rarm->SetPosition(wxPoint(-55, -80));
    torso->AddChild(rarm);

    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(torso);
    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}