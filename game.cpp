#include "game.h"

namespace Game {
  static RoundResult lastRoundResult {};

  void checkRoundResults() {
    Serial.println("Stampa punti. A:" + String(pressesA) + ", B: " + String(pressesB));
    Serial.println("Stampa timer. A:" + String(lastCheckA) + ", B:" + String(lastCheckB));
    if (pressesA == toBePressed && pressesB != toBePressed) {
      scoreA++;
      lastRoundResult = WIN_A;
    } else if (pressesB == toBePressed && pressesA != toBePressed) {
      scoreB++;
      lastRoundResult = WIN_B;
    } else if (pressesA == toBePressed && pressesB == toBePressed) {
      if (lastCheckA < lastCheckB) {
        scoreA++;
        lastRoundResult = WIN_A;
      } else {
        scoreB++;
        lastRoundResult = WIN_B;
      }
    } else lastRoundResult = TIE;
  }

  RoundResult getLastRoundResult() {
    return lastRoundResult;
  }

  float getRatioForDifficulty() {
    return difficultyLevel * 0.05;
  }

  void resetScore() {
    scoreA = 0;
    scoreB = 0;
  }

  void resetPresses() {
    pressesA = 0;
    pressesB = 0;
  }

  void generatePresses() {
    toBePressed = (rand() % 3) + 1; // Number between 1 - 3.
  }

  void generateT1() {
    t1 = (t1 - (t1 * getRatioForDifficulty()));
  }
}
