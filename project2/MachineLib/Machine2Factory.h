/**
 * @file Machine2Factory.h
 * @author Cameron Schwindaman
 *
 * Factory for creating Machine #2
 */

#ifndef CANADIANEXPERIENCE_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINE2FACTORY_H

#include <memory>
#include <string>

class Machine;
class Shape;

/**
 * Factory for creating Machine #2
 */
class Machine2Factory {
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

    //// Create a post
    std::shared_ptr<Shape> CreatePost(int x, int y, int wid, int hit);

public:
    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINE2FACTORY_H
