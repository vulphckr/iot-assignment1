#include "int_handlers.h"
#include "game.h"
#include "proj_utils.h"

bool ledPulsatingRising {}; // true = pulsatingLedValue increasing
int pulsatingLedValue {};         // Current LED phasing value

namespace Handlers {
  // ISR for button A (left)
  void buttonAPress() {
    long curTime = millis();
    if (curTime - lastCheckA > TOLERANCE) {
      lastCheckA = curTime;
      ++scoreA;
    }
  }

  // ISR for button B (right)
  void buttonBPress() {
    long curTime = millis();
    if (curTime - lastCheckB > TOLERANCE) {
      lastCheckB = curTime;
      ++scoreB;
    }
  }

  void readyToPlay() {
    Game::generatePresses();
    Game::generateT1();

    Timer1.detachInterrupt();
    Timer1.initialize(t1 * 1000);
    Timer1.attachInterrupt(Game::checkRoundResults);

    currentStatus = PLAYING;
  }

  bool checkIfBothPressed() {
    if (abs(lastCheckA-lastCheckB) < BOTH_PRESSED_TOLERANCE) {
      long curTime = millis();
      lastCheckA = curTime;
      lastCheckB = curTime + 2*BOTH_PRESSED_TOLERANCE;
      return true;
    }
    else return false;
  }

  void changeLedStatus() {
    if (ledPulsatingRising && (pulsatingLedValue + PULSE_SPEED) >= PULSATING_DIFF) {
      ledPulsatingRising = false;
    } else if (!ledPulsatingRising && pulsatingLedValue <= 0) {
      ledPulsatingRising = true;
    }

    pulsatingLedValue += (ledPulsatingRising ? PULSE_SPEED : -PULSE_SPEED);

    analogWrite(RED_LED_P1, pulsatingLedValue);
    analogWrite(RED_LED_P2, (PULSATING_DIFF - pulsatingLedValue));
  }
}