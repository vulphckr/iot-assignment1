/*
  Header containing all functions regarding the 
  I2C display such as printing text.
*/

#ifndef __DISPLAYPROJ__
#define __DISPLAYPROJ__

#include <LiquidCrystal_I2C.h>
#include "proj_constants.h"

namespace Display {
  void initializeLCD(); // Initializes the LCD display
  void printRotating(); // Prints a "rotating" text on the display.
  void normalPrint();   // Prints a still text on the display, centered on second row.
}

#endif
