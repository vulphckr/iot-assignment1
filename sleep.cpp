#include "sleep.h"

namespace SleepHandler {
  // Checks if 10 seconds of inactivity elasped.
  bool isInactive() {
    return (millis() - lastCheckA) > TIME_UNTIL_DEEP_SLEEP
      && (millis() - lastCheckB) > TIME_UNTIL_DEEP_SLEEP;
  }
  
  // Checks inactivity every time it is called.
  void checkInactivity() {
    if(SleepHandler::isInactive()) {
      // Activate sleeping
      lcd.clear();
      lcd.noBacklight();
      analogWrite(RED_LED_P1, 0);
      analogWrite(RED_LED_P2, 0);
      sleep_enable();
      sleep_mode();

      // Disable sleeping due to interrupt
      sleep_disable();
      lcd.backlight();
      currentStatus = IDLE;
    }
  }
}