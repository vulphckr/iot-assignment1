#include "game.h"

namespace Game {
  void checkRoundResults() {}

  float getRatioForDifficulty() {
    return difficultyLevel * 0.05;
  }

  void resetScore() {
    scoreA = 0;
    scoreB = 0;
  }

  void generatePresses() {
    toBePressed = (rand() % 3) + 1; // Number between 1 - 3.
  }

  void generateT1() {
    t1 = (t1 - (t1 * getRatioForDifficulty()));
  }
}
