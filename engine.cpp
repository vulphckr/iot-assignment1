#include "engine.h"

namespace Engine {
  static Status currentStatus = IDLE; // The status the game is in currently
  static bool roundSetupped {}; // If the round is not setupped

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

    Display::printRotating();
  }

  void starting() {
    Timer1.stop();
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
      generatedTime = ((rand() % 4) + 1) * 1000; 
      timeSinceCountStarted = millis();
      
      Timer1.detachInterrupt();
    }

    if (millis() - timeSinceCountStarted >= generatedTime) {
      Game::generateT1();
      currentStatus = PLAYING;
    }
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
    Display::clear();
    switch (Game::getRoundResult()) {
      case Game::WIN_A: {
        Display::normalPrint("Ha vinto A!");
        Game::increaseScoreA();
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        delay(2000);
        currentStatus = WAITING;
        break;
      }
      case Game::WIN_B: {
        Display::normalPrint("Ha vinto B!");
        Game::increaseScoreB();
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        delay(2000);
        currentStatus = WAITING;
        break;
      }
      case Game::TIE: {
        Display::normalPrint("Pareggio!");
        Display::printScore(Game::getScoreA(), Game::getScoreB());
        Handlers::preventRetrigger();
        delay(2000);
        currentStatus = IDLE;
        break;
      }
    }
  }

  Status getCurrentStatus() {
    return currentStatus;
  }
}