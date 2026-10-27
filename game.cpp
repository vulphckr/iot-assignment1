#include "game.h"

namespace Game {
  // Variables for the scores of the players
  // These are volatile because needs to be edited during execution
  static volatile short scoreA {};
  static volatile short scoreB {};
  static long roundLength { Constants::STARTING_T1 }; // How much the round lasts
  static double difficultyMod {};                     // Difficulty modifier for current round
  static short roundPresses {};                       // How many presses have to be done

  void resetScores() {
    scoreA = 0;
    scoreB = 0;
  }

  short getScoreA() { return scoreA; }
  short getScoreB() { return scoreB; }

  void generateT1() {
    roundLength *= difficultyMod; // TODO: Add difficulty meter
  }

  void setDifficulty() {
    roundLength = Constants::STARTING_T1;
    switch(map(analogRead(Constants::POTENTIOMETER_PIN), 0, 1023, 1, 4)) {
      case 1:
        difficultyMod = Constants::EASY; break;
      case 2:
        difficultyMod = Constants::MEDIUM; break;
      case 3:
        difficultyMod = Constants::HARD; break;
      case 4:
        difficultyMod = Constants::VERY_HARD; break;
      default: difficultyMod = 1; break;
    }
  #ifdef DEBUG
    Serial.println("Modificatore" + String(difficultyMod));
  #endif
  }

  short generatePresses() {
    roundPresses = (rand() % 3) + 1;
    return roundPresses;
  }

  bool tooEarly() {
    return Handlers::getAPresses() != 0 || Handlers::getBPresses() != 0;
  }

  RoundResult manageEarlyPenalty() {
    if (Handlers::getAPresses() != 0) {
      --scoreA;
      digitalWrite(Constants::RED_LED_P1, HIGH);
      return EARLY_A;
    } else {
      --scoreB;
      digitalWrite(Constants::RED_LED_P2, HIGH);
      return EARLY_B;
    }
  }

  bool hasRoundFinished(long timeStamp) {
  #ifdef DEBUG
    Serial.println("Duration of round: " + String(roundLength));
  #endif
    return (millis() - timeStamp >= roundLength);
  }

  RoundResult getRoundResult() {
    short pressesA = { Handlers::getAPresses() };
    short pressesB = { Handlers::getBPresses() };
  #ifdef DEBUG
    Serial.println("Stampa punti. A:" + String(pressesA) + ", B: " + String(pressesB));
  #endif
    if (pressesA == 0 && pressesB == 0) {
      return GAME_OVER;
    }
    if (pressesA == roundPresses && pressesB != roundPresses) {
      digitalWrite(Constants::RED_LED_P2, HIGH);
      --scoreB;
      digitalWrite(Constants::GRN_LED_P1, HIGH);
      ++scoreA;
      return WIN_A;
    } else if (pressesB == roundPresses && pressesA != roundPresses) {
      digitalWrite(Constants::RED_LED_P1, HIGH);
      --scoreA;
      digitalWrite(Constants::GRN_LED_P2, HIGH);
      ++scoreB;
      return WIN_B;
    } else if (pressesA == roundPresses && pressesB == roundPresses) {
      if (Handlers::isAPressedBeforeB()) {
        digitalWrite(Constants::GRN_LED_P1, HIGH);
        ++scoreA;
        return WIN_A;
      } else {
        digitalWrite(Constants::GRN_LED_P2, HIGH);
        ++scoreB;
        return WIN_B;
      }
    } else {
      digitalWrite(Constants::RED_LED_P1, HIGH);
      --scoreA;
      digitalWrite(Constants::RED_LED_P2, HIGH);
      --scoreB;
      return TIE;
    }
  }
}