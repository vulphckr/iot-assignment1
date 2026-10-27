#include "game.h"

namespace Game {
  // Variables for the scores of the players
  // These are volatile because needs to be edited during execution
  static volatile short scoreA {};
  static volatile short scoreB {};
  static long roundLength {};                // How much the round lasts
  static short roundPresses {};              // How many presses have to be done

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

  void generateT1() {
    roundLength = 2000; // TODO: Add difficulty meter
  }

  short generatePresses() {
    roundPresses = (rand() % 3) + 1;
    return roundPresses;
  }

  bool hasRoundFinished(long timeStamp) {
    return (millis() - timeStamp >= roundLength);
  }

  RoundResult getRoundResult() {
    short pressesA = { Handlers::getAPresses() };
    short pressesB = { Handlers::getBPresses() };
  #ifdef DEBUG
    Serial.println("Stampa punti. A:" + String(pressesA) + ", B: " + String(pressesB));
  #endif
    if (pressesA == roundPresses && pressesB != roundPresses) {
      return WIN_A;
    } else if (pressesB == roundPresses && pressesA != roundPresses) {
      return WIN_B;
    } else if (pressesA == roundPresses && pressesB == roundPresses) {
      if (Handlers::isAPressedBeforeB()) {
        return WIN_A;
      } else {
        return WIN_B;
      }
    } else return TIE;
  }
}