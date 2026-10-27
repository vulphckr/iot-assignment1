/*
  Header containing all the constants of the project.
  These include:
   - Pins for LEDs, buttons...
   - The LCD Screen, which will be considered as "extern"
   - Game & other settings (debounce, max time of waiting...)
*/
#ifndef __PROJCONST__
#define __PROJCONST__

#include <Arduino.h>
#include <TimerOne.h> // For Timer1 management
// Removing the following comment will enable debug prints.
#define DEBUG

namespace Constants {
  // Button Pins
  constexpr int BUTTON_A_PIN { 2 }; // Left Button
  constexpr int BUTTON_B_PIN { 3 }; // Right Button

  // LED Pins
  constexpr int RED_LED_P1 { 5 };               // Red LED (Left)
  constexpr int RED_LED_P2 { 6 };               // Red LED (Right)
  constexpr int GRN_LED_P1 { 7 };               // Green LED (Left)
  constexpr int GRN_LED_P2 { 8 };               // Green LED (Right)

  // Serial & LCD Communication 
  constexpr int BAUD_RATE { 9600 };             // For serial transmission
  constexpr int LCD_ADDR { 0x27 };              // LCD Registry Address
  constexpr int LCD_WIDTH { 20 };               // LCD Display Width (in columns)
  constexpr int LCD_HEIGHT { 4 };               // LCD Display Height (in rows)

  // Pulsating LEDs
  constexpr int PULSE_INTERVAL { 50000 };       // Pulsing LED interval
  constexpr int MAX_PULSE_VAL { 255 };          // Maximum pulsation value
  constexpr int PULSE_SPEED { 10 };             // Changes the speed of the pulsation (both fading/rising)

  // Behavior-related constants
  constexpr int DEEP_SLEEP_TIME { 10000 };      // Time until the system goes into deep sleep (in ms)
  constexpr int BUTTON_TOLERANCE { 190 };       // Button tolerance to avoid debounce
  constexpr int TEXT_SPEED { 200 };             // Text scrolling speed
  constexpr int BOTH_PRESSED_TOLERANCE { 500 }; // Time span for both buttons to be considered as pressed toghether
  constexpr int MAX_WAITING_TIME { 5000 };      // Maximum amount of time possible to wait between each round
  constexpr int SCORE_DIGITS { 3 };             // Maximum digits of the score
}
#endif