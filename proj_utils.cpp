#include "proj_utils.h"

// Definition for externed variables
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); 
volatile long lastCheckA {};
volatile long lastCheckB {};
Status currentStatus = IDLE;

short scoreA {};
short scoreB {};

volatile short pressesA {};
volatile short pressesB {};

short toBePressed {};
int t1 { 2000 };
short difficultyLevel { 2 }; 