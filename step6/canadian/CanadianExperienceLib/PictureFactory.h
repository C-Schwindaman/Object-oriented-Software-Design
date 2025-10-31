/**
 * @file PictureFactory.h
 * @author Cameron Schwindaman
 *
 * A factory class that builds our picture.
 */
 
#ifndef PICTUREFACTORY_H
#define PICTUREFACTORY_H

class Picture;

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
private:

public:
    std::shared_ptr<Picture> Create(std::wstring imagesDir);

};

#endif //PICTUREFACTORY_H