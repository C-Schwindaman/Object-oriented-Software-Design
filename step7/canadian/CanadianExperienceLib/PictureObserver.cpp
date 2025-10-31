/**
 * @file PictureObserver.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "PictureObserver.h"
#include "Picture.h"

/**
 * Destructor
 */
PictureObserver::~PictureObserver()
{
    if (mPicture != nullptr)
    {
        mPicture->RemoveObserver(this);
    }
}

/**
 * Set the picture for this observer
 * @param picture The picture to set
 */
void PictureObserver::SetPicture(std::shared_ptr<Picture> picture)
{
    mPicture = picture;
    mPicture->AddObserver(this);
}

/**
 * Get the picture from this observer
 * @return The picture to get
 */
std::shared_ptr<Picture> PictureObserver::GetPicture()
{
    return mPicture;
}