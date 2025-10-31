/**
 * @file PictureObserver.h
 * @author Cameron Schwindaman
 *
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
 
#ifndef PICTUREOBSERVER_H
#define PICTUREOBSERVER_H

#include <memory>

class Picture;

/**
 * Observer base class for a picture.
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected:
    /// Constructor
    PictureObserver() {}

public:
    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver &) = delete;
    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual ~PictureObserver();
    void SetPicture(std::shared_ptr<Picture> picture);
    std::shared_ptr<Picture> GetPicture();
};

#endif //PICTUREOBSERVER_H