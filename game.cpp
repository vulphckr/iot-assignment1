#include "game.h"

namespace Game {
  // Variables for the scores of the players
  // These are volatile because needs to be edited during execution
  static volatile short scoreA {};
  static volatile short scoreB {};

  void increaseScoreA() { ++scoreA; }
  void increaseScoreB() { ++scoreB; }
  void decreaseScoreA() { --scoreA; }
  void decreaseScoreB() { --scoreB; } 
  void resetScores() {
    scoreA = 0;
    scoreB = 0;
  }

  short getScoreA() { return scoreA; }
  short getScoreB() { return scoreB; }
}