#include "engine.h"

namespace Engine {
  static Status currentStatus = IDLE; // The status the game is in currently
  static bool roundSetupped {}; // If the round is not setupped
  static bool showWin {};

  void idle() {
    // Resets to IDLE if the system wakes up from Deep Sleep
    if (currentStatus != IDLE) {
      currentStatus = IDLE;
      return;
    }

    // If both buttons are pressed, start the round
    if(Handlers::checkIfBothPressed()) {
      currentStatus = STARTING;
      return;
    }

    Display::printRotating("");
  }

  void starting() {
    Timer1.stop();
    digitalWrite(Constants::RED_LED_P1, LOW);
    digitalWrite(Constants::RED_LED_P2, LOW);
  #ifdef DEBUG
    Serial.println("Potenziometro: " + String(analogRead(Constants::POTENTIOMETER_PIN)));
  #endif
    Game::setDifficulty();
    Game::resetScores();
    Handlers::resetPresses();
    Display::clear();
    Display::normalPrint();
    Display::printScore(Game::getScoreA(), Game::getScoreB());
    delay(3000); // Busy Waiting here is OK.
    currentStatus = WAITING; // Move to WAITING
  }

  void waiting() {
    /* 
      Variables for managing time without busy waiting
      This allows for buttons to be pressed during this time
      And eventually give a penalty.
    */
    static unsigned long timeSinceCountStarted {};
    static long generatedTime {};
    
    if(!roundSetupped) {
  #ifdef DEBUG
      Serial.println("Round is being setupped.");
  #endif
      roundSetupped = true;

      Display::clear();
      Handlers::resetPresses();
      Display::normalPrint();

      digitalWrite(Constants::GRN_LED_P1, LOW);
      digitalWrite(Constants::GRN_LED_P2, LOW);
      digitalWrite(Constants::RED_LED_P1, LOW);
      digitalWrite(Constants::RED_LED_P2, LOW);

      generatedTime = ((rand() % 4) + 1) * 1000; 
      timeSinceCountStarted = millis();
      
      Timer1.detachInterrupt();
    }

    if (millis() - timeSinceCountStarted >= generatedTime) {
      Game::generateT1();
      currentStatus = PLAYING;
    }

    if (Game::tooEarly()) {
      currentStatus = TOO_EARLY;
    } 
  }

  void too_early() {
    roundSetupped = false;
    switch (Game::manageEarlyPenalty()) {
      case Game::EARLY_A: Display::normalPrint("P1 pressed too early"); break;
      case Game::EARLY_B: Display::normalPrint("P2 pressed too early"); break;
      default: break;
    }
    Display::printScore(Game::getScoreA(), Game::getScoreB());
    delay(2000);
    currentStatus = WAITING;
  }

  void playing() {
    static long roundTimeStart {};

    if(roundSetupped) {
      roundSetupped = false;
      Display::clear();
      // Generates and prints the number of presses
      Display::normalPrint(String(Game::generatePresses()));
      roundTimeStart = millis();
    }

    if (Game::hasRoundFinished(roundTimeStart)) {
      currentStatus = RESULT;
    }
  }

  void result() {
    switch (Game::getRoundResult()) {
      case Game::WIN_A: {
        Display::clear();
        Display::normalPrint("P1 got the point!");
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        delay(2000);
        currentStatus = WAITING;
        break;
      }
      case Game::WIN_B: {
        Display::clear();
        Display::normalPrint("P2 got the point!");
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        delay(2000);
        currentStatus = WAITING;
        break;
      }
      case Game::TIE: {
        Display::clear();
        Display::normalPrint("Tie!");
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        delay(2000);
        currentStatus = WAITING;
        break;
      }
      case Game::GAME_OVER: {
        static long timeSinceCountStarted {};

        if(!showWin) {
          showWin = true;
          timeSinceCountStarted = millis();
          Display::clear();
        }
        String toPrint = "Game Over - ";
        toPrint += ((Game::getScoreA() == Game::getScoreB()) ? "Tie!"
          :(Game::getScoreA() > Game::getScoreB()) ? "P1 Wins!    " : "P2 Wins!    ");
        Display::printRotating(toPrint);
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        Handlers::preventRetrigger();
        if (millis() - timeSinceCountStarted >= Constants::WIN_SHOW_TIME) {
          Display::clear();
          Timer1.start();
          showWin = false;
          currentStatus = IDLE;
        }
        break;
      }
      default: return;
    }
  }

  Status getCurrentStatus() {
    return currentStatus;
  }
}