/*
  Header containing all functions regarding interrupts
  expecially regarding button behavior and timer-related actions.
*/

#ifndef __INTHANDLERS__
#define __INTHANDLERS__

#include "proj_constants.h"

namespace Handlers {
  // For the buttons
  void buttonAPress();            // ISR for left button
  void buttonBPress();            // ISR for right button
  short getAPresses();            // Returns the presses for button A
  short getBPresses();            // Returns the presses for button B
  void resetPresses();            // Reset the presses of both buttons

  // For the game
  bool isInactive();              // Checks if the program should go in deep sleep
  bool checkIfBothPressed();      // Checks if both of the buttons are pressed in a specific moment
  void preventRetrigger();        // Prevents the retrigger of both buttons being pressed
  void changeLedStatus();         // Timer-driven interrupt for managing the fading LEDs
  void initializeButtonPresses(); // Initializes button presses to a default value
  bool isAPressedBeforeB();       // Checks if button A was pressed before button B
}

#endif