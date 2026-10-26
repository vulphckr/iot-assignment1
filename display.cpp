#include "display.h"

namespace Display {
  static LiquidCrystal_I2C display {
      LiquidCrystal_I2C(
        Constants::LCD_ADDR,
        Constants::LCD_WIDTH,
        Constants::LCD_HEIGHT
      )
    }; // Display which will be used for printing

  void initializeLCD() {
    display.init();
    display.backlight();
    display.setCursor(0,0);
  }
  void printRotating() {} // Prints a "rotating" text on the display.
  void normalPrint() {}   // Prints a still text on the display, centered on second row.
}