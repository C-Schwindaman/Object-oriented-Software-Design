/**
 * @file Scoreboard.h
 * @author Serena Brown
 *
 *
 */

#ifndef BOGGLES_GAMELIB_SCOREBOARD_H
#define BOGGLES_GAMELIB_SCOREBOARD_H

/**
 * Up-call of game
 */
class Game;

/**
 * Class that keeps track of the scoreboard (specifically timer based)
 */
class Scoreboard {
    private:
        /// Elapsed time in seconds
        double mElapsedTime = 0.0;
        /// the game itself
        Game* mGame = nullptr;
        /// member variable for the penalty time
        double mPenaltyTime = 0.0;
        /// member variable for the amount of penalty strikes
        int mPenaltyStrikes = 0;

    public:
        /**
         * Constructor
         */
        Scoreboard() = default;

        void Update(double elapsed);
        void Draw(std::shared_ptr<wxGraphicsContext> gc);
        void Reset();
        void AddPenaltyMinute();

        /**
         * Sets the member variable mGame to the game itself
         * @param game
         */
        void SetGame(Game* game) { mGame = game; }
};

#endif //BOGGLES_GAMELIB_SCOREBOARD_H
