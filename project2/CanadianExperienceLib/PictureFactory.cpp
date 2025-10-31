/**
 * @file PictureFactory.cpp
 *
 * @author Charles Owen
 * @author Anik Momtaz
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add a machine
    auto machine1Actor = std::make_shared<Actor>(L"Machine 1");
    machine1Actor->SetPosition(wxPoint(300, 500));

    auto machine1Drawable = std::make_shared<MachineDrawable>(resourcesDir, 1);
    machine1Actor->AddDrawable(machine1Drawable);
    machine1Actor->SetRoot(machine1Drawable);

    picture->AddActor(machine1Actor);

    // Create and add another machine
    auto machine2Actor = std::make_shared<Actor>(L"Machine 2");
    machine2Actor->SetPosition(wxPoint(1000, 500));

    auto machine2Drawable = std::make_shared<MachineDrawable>(resourcesDir, 2);
    machine2Actor->AddDrawable(machine2Drawable);
    machine2Actor->SetRoot(machine2Drawable);

    picture->AddActor(machine2Actor);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(650, 620));
    picture->AddActor(sparty);

    return picture;
}

