#ifndef __PROJENGINE__
#define __PROJENGINE__

#include "proj_constants.h"
#include "handlers.h"
#include "game.h"
#include "display.h"

namespace Engine {
  // Enum for managing the different game status
  typedef enum {
    IDLE,           // Game not started, in sort of "main menu" (either after boot, after deep sleep or after Tie)
    STARTING,       // The game is starting (both buttons pressed)
    WAITING,        // A round is about to be played - random amount of wait
    PLAYING,        // A round is being played
    RESULT          // The round result is shown
  } Status;

  Status getCurrentStatus();      // Returns the current game status
  void idle();                    // Manages the IDLE status
  void starting();                // Manages the STARTING status
  void waiting();                 // Manages the WAITING status
  void playing();                 // Manages the PLAYING status
  void result();                  // Manages the RESULT status
}

#endif