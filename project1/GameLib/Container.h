/**
 * @file Container.h
 * @author Cameron Schwindaman
 *
 * A class for container objects
 */

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Game.h"
#include "Item.h"
#include "Letter.h"

/**
 * A class for container objects
 */
class Container : public Item
{
private:
	/// The base image of the container
    std::unique_ptr<wxImage> mBaseImage;
    /// The front image of the container
    std::unique_ptr<wxImage> mFrontImage;

	/// The base bitmap of the container
    std::unique_ptr<wxBitmap> mBaseBitmap;
    /// The front bitmap of the container
    std::unique_ptr<wxBitmap> mFrontBitmap;

	/// Letters held inside of the container
	std::vector<std::shared_ptr<Letter>> mLetters;
	/// Has the container been headbutted?
	bool mHeadbutted = false;

public:
	/// Default constructor (disabled)
	Container() = delete;

	/// Copy constructor (disabled)
	Container(const Container &) = delete;

	/// Assignment operator
	void operator=(const Container &) = delete;

	Container(Game* game, const std::wstring &filename, const std::wstring &filename2);
	/**
	 * Accept a visitor
	 * @param visitor The visitor to accept
	 */
	void Accept(Visitor* visitor) override;

	/**
	 * Headbutt the container to release letters
	 * @return True if letters were released
	 */
	bool Headbutt();

	/**
	 * Add a letter to the container
	 * @param letter The letter to add
	 */
	void AddLetter(std::shared_ptr<Letter> letter);

	/**
	 * Release letters from the container
	 * Scatters them in a random pattern above the container
	 */
	void ReleaseLetters();

	/**
	 * Is it a container?
	 * @return True
	 */
	bool IsContainer() const override { return true; }

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	/**
	 * Was it headbutted?
	 * @return True if it was headbutted
	 */
	bool WasHeadbutted() const { return mHeadbutted; }
};

#endif //CONTAINER_H