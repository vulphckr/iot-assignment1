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
  void initializeLCD();                         // Initializes the LCD display
  void turnOff();                               // Turns off the LCD
  void turnOn();                                // Turns on the LCD
  void clear();                                 // Clears the LCD once
  void printRotating(String toPrint);           // Prints rotating string. If not specified fallbacks a default string
  void normalPrint();                           // Prints a still text on the display, centered on second row
  void normalPrint(String toPrint);             // Same as before, but the value to print is specified
  void printScore(short scoreA, short scoreB);  // Prints the specified scores on the last row
}

#endif