/*
  Header containing all functions regarding the 
  I2C display such as printing text.
*/

#ifndef __DISPLAYPROJ__
#define __DISPLAYPROJ__

#include <LiquidCrystal_I2C.h>
#include "engine.h"
#include "proj_constants.h"

namespace Display {
  void initializeLCD(); // Initializes the LCD display
  void turnOff();       // Turns off the LCD
  void turnOn();        // Turns on the LCD
  void printRotating(); // Prints a "rotating" text on the display.
  void normalPrint();   // Prints a still text on the display, centered on second row.
}

#endif