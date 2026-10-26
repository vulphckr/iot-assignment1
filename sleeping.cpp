#include "sleeping.h"

namespace Sleeping {
  void manageDeepSleep() {
    // Deep sleeping - turns off display, LEDs and enables sleep
    Display::turnOff();
    analogWrite(Constants::RED_LED_P1, 0);
    analogWrite(Constants::RED_LED_P2, 0);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode(); // From now on the system goes into deep sleep
    
    // Recovery - turns on display, gets back to main menu
    Display::turnOn();
    Engine::idle();
  }
}