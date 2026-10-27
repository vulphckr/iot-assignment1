#include "display.h"
#include "engine.h"
#include "handlers.h"
#include "proj_constants.h"
#include "sleeping.h"


// Setup everything that is wired
void setup() {
  #ifdef DEBUG
  Serial.begin(Constants::BAUD_RATE); // Only enabled if debug is enabled
  #endif

  srand(analogRead(A0)); // Seeding for random number generation
  Handlers::initializeButtonPresses();

  // Buttons
  pinMode(Constants::BUTTON_A_PIN, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(Constants::BUTTON_A_PIN), 
    Handlers::buttonAPress, 
    RISING
  );

  pinMode(Constants::BUTTON_B_PIN, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(Constants::BUTTON_B_PIN), 
    Handlers::buttonBPress, 
    RISING
  );

  // LEDs
  pinMode(Constants::RED_LED_P1, OUTPUT);
  pinMode(Constants::RED_LED_P2, OUTPUT);
  pinMode(Constants::GRN_LED_P1, OUTPUT);
  pinMode(Constants::GRN_LED_P2, OUTPUT);

  // LCD I2C Screen
  Display::initializeLCD();

  // Timer for fading LEDs
  Timer1.initialize(Constants::PULSE_INTERVAL);
  Timer1.attachInterrupt(Handlers::changeLedStatus);
}

void loop() {
  if(Handlers::isInactive()) {
  Sleeping::manageDeepSleep();
  }

  switch (Engine::getCurrentStatus()) {
    case Engine::IDLE: Engine::idle();          return;
    case Engine::STARTING: Engine::starting();  return;
    case Engine::WAITING: Engine::waiting();    return;
    case Engine::PLAYING: Engine::playing();    return;
    case Engine::RESULT: Engine::result();      return;
    default: return;
  }
}
