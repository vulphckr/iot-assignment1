/*
  Header containing all functions regarding interrupts
  expecially regarding button behavior and timer-related actions.
*/

#ifndef __INTHANDLERS__
#define __INTHANDLERS__

#include "proj_constants.h"

namespace Handlers {
  void buttonAPress();            // ISR for left button
  void buttonBPress();            // ISR for right button
  bool isInactive();              // Checks if the program should go in deep sleep
  void changeLedStatus();         // Timer-driven interrupt for managing the fading LEDs
  void initializeButtonPresses(); // Initializes button presses to a default value
}

#endif