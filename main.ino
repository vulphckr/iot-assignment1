#include <time.h>
#include "int_handlers.h"
#include "sleep.h"
#include "display.h"
#include "game.h"
#include "proj_utils.h"

volatile bool roundSetupped {};

// Setupping
void setup() {
  Serial.begin(9600);   // TODO: remove when finished - only used for debugging.
  srand(analogRead(A0)); // TODO: find a better way to generate random numbers.
  lastCheckA = millis(); // initialize lastCheck when starting the MCU.
  lastCheckB = lastCheckA + BOTH_PRESSED_TOLERANCE;

  // Buttons
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), Handlers::buttonAPress, RISING);

  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), Handlers::buttonBPress, RISING);

  // Fading Red LEDs
  pinMode(RED_LED_P1, OUTPUT);
  pinMode(RED_LED_P2, OUTPUT);
  pinMode(GRN_LED_P1, OUTPUT);
  pinMode(GRN_LED_P2, OUTPUT);

  // LCD I2C screen
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Timer(s)
  Timer1.initialize(50000);
  Timer1.attachInterrupt(Handlers::changeLedStatus); 
}

void loop() {
  SleepHandler::checkInactivity();

  switch(currentStatus){
    case IDLE: {
        Display::printRotating();
        if (Handlers::checkIfBothPressed()) {
          lcd.clear();
          analogWrite(RED_LED_P1, 0);
          analogWrite(RED_LED_P2, 0);
          Timer1.detachInterrupt();
          currentStatus = STARTING;
        }
        break;
      }
    case STARTING: {
      Game::resetScore();
      Display::normalPrint();
      delay(2000);
      currentStatus = WAITING;
      break;
    }
    case WAITING: {
      static unsigned long waitingStartTime = 0;
      static long generatedTimeMS = 0;
      
      if(!roundSetupped) {
        roundSetupped = true;
        lcd.clear();

        Game::resetPresses();
        Display::normalPrint();
        generatedTimeMS = ((rand() % 4) + 1) * 1000; 
        waitingStartTime = millis();
        
        Timer1.detachInterrupt();
      }

      if (millis() - waitingStartTime >= generatedTimeMS) {
        Handlers::readyToPlay(); // Questa va in Game.
      }
      break;
    }
    case PLAYING: {
      static unsigned long roundTime = 0;

      if(roundSetupped) {
        roundSetupped = false;
        lcd.clear();
        Display::normalPrint();
        roundTime = millis();
      }
      if (millis() - roundTime >= t1) {
        currentStatus = RESULT;
      }
      break;
    }

    case RESULT:
      Game::checkRoundResults();
      Display::normalPrint();
      delay(5000); // Da rimuovere perchè deve scorrere e fa schifo
      currentStatus = WAITING;
      Serial.println("Yo!");
    break;

    default: {delay(200);}
  }
}