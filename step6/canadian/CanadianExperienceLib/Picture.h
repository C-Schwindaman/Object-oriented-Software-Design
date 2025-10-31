/**
 * @file Picture.h
 * @author Cameron Schwindaman
 *
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
 
#ifndef PICTURE_H
#define PICTURE_H

#include <vector>

class PictureObserver;
class Actor;

/**
 * The picture we are drawing.
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// The actors of this picture
    std::vector<std::shared_ptr<Actor>> mActors;

public:
    /**
     * Constructor
     */
    Picture() {}

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void AddActor(std::shared_ptr<Actor> actor);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /** Iterator that iterates over actors */
    class ActorIter
    {
    public:
        /**
         * Constructor
         * @param actors The collection we are iterating over
         * @param pos Position in the collection
         */
        ActorIter(std::vector<std::shared_ptr<Actor>> actors, int pos) : mActors(actors), mPos(pos) {}

        /**
         * Compare two iterators
         * @param other The other iterator we are comparing to
         * @return  true if this position is not equal to the other position
        */
        bool operator!=(const ActorIter &other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Actor> operator *() const { return mActors[mPos]; }

        /**
         * Increment the iterator, moving to the next item in the collection
         * @return Reference to this iterator
         */
        const ActorIter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        std::vector<std::shared_ptr<Actor>> mActors;   ///< Actors we are iterating over
        int mPos;                  ///< Position in the collection
    };

    /** Get an iterator for the beginning of the collection
     * @return Iter object at position 0 */
    ActorIter begin() { return ActorIter(mActors, 0); }

    /** Get an iterator for the end of the collection
     * @return Iter object at position past the end */
    ActorIter end() { return ActorIter(mActors, mActors.size()); }
};

#endif //PICTURE_H