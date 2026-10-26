#include "handlers.h"

namespace Handlers {
  // Variables that contain the timestamp of the last button press.
  static volatile long lastCheckA {};
  static volatile long lastCheckB {};

  // Variables that contain the number of presses of each button.
  static volatile short pressesA {};
  static volatile short pressesB {};

  // Rising/Fading LEDs variables
  int pulsatingLedValue {}; // current phase value
  static bool isRising {};  // true = phase increasing

  void buttonAPress() {
    long curTime = millis();
    // Debounce prevention: a click will be regirested if outside of tolerance.
    if (curTime - lastCheckA > Constants::BUTTON_TOLERANCE) {
      lastCheckA = curTime;
      ++pressesA;
    }
  };

  void buttonBPress() {    
    long curTime = millis();
    // Debounce prevention here as well.
    if (curTime - lastCheckB > Constants::BUTTON_TOLERANCE) {
      lastCheckB = curTime;
      ++pressesB;
    }
  };

  bool isInactive() {
    // If both of the buttons are not pressed within TIME_UNTIL_DEEP_SLEEP, the system goes into deep sleep.
    return (millis() - lastCheckA) > Constants::DEEP_SLEEP_TIME
      && (millis() - lastCheckB) > Constants::DEEP_SLEEP_TIME;
  }
  
  // Timer interrupt for managing the rising/fading Red LEDs.
  void changeLedStatus() {
    // Check if value overflows MAX_PULSE_VAL or underflows 0
    if (isRising && (pulsatingLedValue + Constants::PULSE_SPEED) >= Constants::MAX_PULSE_VAL) {
      isRising = false;
    } else if (!isRising && pulsatingLedValue <= 0) {
      isRising = true;
    }

    // Writes the value to both LEDs
    pulsatingLedValue += (isRising ? Constants::PULSE_SPEED : -Constants::PULSE_SPEED);

    analogWrite(Constants::RED_LED_P1, pulsatingLedValue);
    analogWrite(Constants::RED_LED_P2, (Constants::MAX_PULSE_VAL - pulsatingLedValue));
  };

  void initializeButtonPresses() {
      lastCheckA = millis();
      // Adding a delay for not being considered as pressed toghether at first.
      lastCheckB = lastCheckA + Constants::BOTH_PRESSED_TOLERANCE;
  };
}
