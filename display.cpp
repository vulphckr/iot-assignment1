#include "display.h"

namespace Display {
  static signed int currentChar {};       // Current rotation character
  static unsigned long lastScrollTime {}; // Last time a scroll was made
  static LiquidCrystal_I2C display {
      LiquidCrystal_I2C(
        Constants::LCD_ADDR,
        Constants::LCD_WIDTH,
        Constants::LCD_HEIGHT
      )
    }; // Display which will be used for printing

  String getStringForGameStatus() {
    switch(Engine::getCurrentStatus()) {
      case Engine::IDLE:
        return "Welcome to the React! Game. Press Buttons to Start.    ";
      default:
        return "";
    }
  }

  void initializeLCD() {
    display.init();
    display.backlight();
    display.setCursor(0,0);
  }

  // Turns off the LCD - used for deep sleeping
  void turnOff() {
    display.clear();
    display.noBacklight();
  }

  // Turns the LCD back on - used for deep sleeping
  void turnOn() {
    display.backlight();
  }

  void printRotating() {
    // First, we check if a scroll has to be made
    // We use this instead of delay() for preventing busy waiting
    unsigned long currentMillis = millis();

    if (currentMillis - lastScrollTime < Constants::TEXT_SPEED) {
        return; 
    }

    // Performing the scroll
    lastScrollTime = currentMillis;
    display.clear();
    String fullText = getStringForGameStatus();

    // Padding for text - adds spaces until LCD_WIDTH + 5 (if necessary)
    while (fullText.length() < Constants::LCD_WIDTH + 5) {
      fullText += " ";
    }

    // Prints current substring and eventually appending text to be repeated
    String toBeDisplayed = fullText.substring(currentChar, currentChar + Constants::LCD_WIDTH);
    int len = toBeDisplayed.length();

    if (len < Constants::LCD_WIDTH) {
        toBeDisplayed += fullText.substring(0, Constants::LCD_WIDTH - len);
    }

    display.setCursor(0, 1);
    display.print(toBeDisplayed);
    currentChar = (currentChar < fullText.length()) ? (currentChar + 1) : 0;
  }

  void normalPrint() {}   // Prints a still text on the display, centered on second row.
}