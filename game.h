#ifndef __PROJGAME__
#define __PROJGAME__

#include "proj_constants.h"
#include "handlers.h"

namespace Game {
  // Enum for managing round results
  typedef enum {
    WIN_A,
    WIN_B,
    EARLY_A,
    EARLY_B,
    TIE,
    GAME_OVER
  } RoundResult;

  // Scoring system
  void resetScores();                     // Resets both the scores

  short getScoreA();                      // Returns the score for player A
  short getScoreB();                      // Returns the score for player B

  void generateT1();                      // Generates round time duration
  void setDifficulty();                   // Set difficulty based off the pot sensor.
  short generatePresses();                // Generates round presses to be made

  bool tooEarly();                        // True if someone pressed early
  RoundResult manageEarlyPenalty();       // Manages the penalty of the player who pressed early
  bool hasRoundFinished(long timeStamp);  // Checks if round has finished
  RoundResult getRoundResult();           // At the end of the round, gets the result
}

#endif