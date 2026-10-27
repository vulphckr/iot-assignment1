#ifndef __PROJGAME__
#define __PROJGAME__

#include "proj_constants.h"
#include "handlers.h"

namespace Game {
  // Enum for managing round results
  typedef enum {
    WIN_A,
    WIN_B,
    TIE
  } RoundResult;

  // Scoring system
  void resetScores();                     // Resets both the scores
  void increaseScoreA();                  // Increases A score
  void increaseScoreB();                  // Increases B score
  void decreaseScoreA();                  // Decreases A score
  void decreaseScoreB();                  // Decreases B score

  short getScoreA();                      // Returns the score for player A
  short getScoreB();                      // Returns the score for player B

  void generateT1();                      // Generates round time duration
  short generatePresses();                // Generates round presses to be made

  bool hasRoundFinished(long timeStamp);  // Checks if round has finished
  RoundResult getRoundResult();            // At the end of the round, gets the result
}

#endif