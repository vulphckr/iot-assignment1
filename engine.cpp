#include "engine.h"

namespace Engine {
  Status currentStatus = IDLE; // The status the game is in currently

  void idle() {
    // Resets to IDLE if the system wakes up from Deep Sleep
    if (currentStatus != IDLE) {
      currentStatus = IDLE;
      return;
    }

    Display::printRotating();
    delay(200);
  }

  Status getCurrentStatus() {
    return currentStatus;
  }
}