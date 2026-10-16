#ifndef __PROJECTUTILS__
#define __PROJECTUTILS__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TimerOne.h>
#include <avr/sleep.h>
#include "Arduino.h"

// Components
extern LiquidCrystal_I2C lcd;                   // LCD display

constexpr int BUTTON_A_PIN { 2 };               // Button A, on the left
constexpr int BUTTON_B_PIN { 3 };               // Button B, on the right
constexpr int RED_LED_P1 { 5 };                 // Red LED, on the left
constexpr int RED_LED_P2 { 6 };                 // Red LED, on the right
constexpr int GRN_LED_P1 { 7 };                 // Green LED, on the left
constexpr int GRN_LED_P2 { 8 };                 // Green LED, on the right

// Behavioral
constexpr int PULSATING_DIFF { 255 };           // Maximum value for the pulsating LEDs
constexpr int PULSE_SPEED { 10 };               // Pulse speed for the pulsating LEDs
constexpr long TIME_UNTIL_DEEP_SLEEP { 20000 }; // Time for deep sleeping due to inactivity
constexpr long TOLERANCE { 190 };               // Debounce tolerance for the buttons
constexpr long BOTH_PRESSED_TOLERANCE { 500 };  // Window of time where the buttons can be considered as pressed simultaneously
constexpr long MAX_TIME { 5000 };            // Maximum window of times between rounds

// Buttons
extern volatile long lastCheckA;                 // Variable which contains the last time since the last interaction
extern volatile long lastCheckB;                 // Variable which contains the last time since the last interaction

// Game variables
extern short scoreA;                             // The score of Player A (left)
extern short scoreB;                             // The score of Player B (right)
extern volatile short pressesA;                  // Player A presses during the game
extern volatile short pressesB;                  // Player B presses during the game
extern int t1;                                   // Reaction time for every round
extern short difficultyLevel;                    // Reaction time modifier given by pot device
extern short toBePressed;                        // Number of times the button has to be pressed

// Possible game statuses
typedef enum {
    IDLE,
    STARTING,
    WAITING,
    PLAYING,
    WIN,
    TIE
} Status;

extern Status currentStatus;
#endif
