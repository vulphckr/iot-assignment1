#ifndef __PROJGAME__
#define __PROJGAME__

#include "proj_constants.h"

namespace Game {
  void increaseScoreA();    // Increases A score
  void increaseScoreB();    // Increases B score
  void decreaseScoreA();    // Decreases A score
  void decreaseScoreB();    // Decreases B score
  void resetScores();       // Resets both the scores

  short getScoreA();        // Returns the score for player A
  short getScoreB();        // Returns the score for player B
}

#endif