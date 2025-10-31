/**
 * @file HaroldFactory.h
 * @author Cameron Schwindaman
 *
 * Factory class that builds the Harold character
 */
 
#ifndef HAROLDFACTORY_H
#define HAROLDFACTORY_H

class Actor;

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //HAROLDFACTORY_H