#include "engine.h"

namespace Engine {
  Status currentStatus = IDLE; // The status the game is in currently

  void idle() {
    // Resets to IDLE if the system wakes up from Deep Sleep
    if (currentStatus != IDLE) {
      currentStatus = IDLE;
      return;
    }

    if(Handlers::checkIfBothPressed()) {
      currentStatus = STARTING;
      return;
    }

    Display::printRotating();
  }

  void starting() {
    Timer1.stop();
    Display::clear();
    Display::normalPrint();
    Display::printScore(Game::getScoreA(), Game::getScoreB());
    delay(3000); // Busy Waiting here is OK.
    currentStatus = IDLE; // Move to WAITING
  }

  Status getCurrentStatus() {
    return currentStatus;
  }
}