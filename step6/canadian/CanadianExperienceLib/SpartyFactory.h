/**
 * @file SpartyFactory.h
 * @author Cameron Schwindaman
 *
 * Factory class that builds the Sparty character
 */
 
#ifndef SPARTYFACTORY_H
#define SPARTYFACTORY_H

class Actor;

/**
 * Factory class that builds the Sparty character
 */
class SpartyFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //SPARTYFACTORY_H