#include "display.h"
#include "proj_utils.h"
#include <string.h>

constexpr int DISPLAY_X_SIZE { 20 };
constexpr int SCORE_DIGITS { 2 };
constexpr char IDLE_TEXT[] { "Welcome to the React! Game. Press Buttons to Start    " };
constexpr char STARTING_TEXT[] { "Go!" };
constexpr char WAITING_TEXT[] { "Ready..." };
constexpr char PLAYING_TEXT[] { "Is this niggerlicious" };
int currentChar {};

const char* getDisplayTextForStatus() {
    switch(currentStatus) {
        case IDLE:
            return IDLE_TEXT;
        case STARTING:
            return STARTING_TEXT;
        case WAITING:
            return WAITING_TEXT;
        case PLAYING:
            return PLAYING_TEXT;
        default:
            return "";
    }
}

void getLeadingSubString(char* str, char* buf, int startLen, int endLen) {
    int len = strlen(str);
    if(!len <= endLen) {
        for(int i = 0; i < endLen; i++) {
            int charIndex = (startLen + i) % len;
            buf[i] = str[charIndex];
        }
        buf[endLen] = '\0';
    }
}

void printScore() {
    lcd.setCursor(SCORE_DIGITS, 3);
    lcd.print(scoreA);
    lcd.setCursor(DISPLAY_X_SIZE - SCORE_DIGITS - 1, 3);
    lcd.print(scoreB);
}

namespace Display {
    void printRotating() {
        char buffer[DISPLAY_X_SIZE + 1];
        char* displayed = getDisplayTextForStatus();
        getLeadingSubString(displayed, buffer, currentChar, DISPLAY_X_SIZE);
        lcd.setCursor(0, 1);
        lcd.print(buffer);
        currentChar = (currentChar <= strlen(displayed) ? (currentChar+1) : 0);
        delay(50);
    }

    void normalPrint() {
        char* displayed = getDisplayTextForStatus();
        lcd.setCursor(((DISPLAY_X_SIZE - strlen(displayed) + 1) / 2), 1);
        lcd.print(displayed);
        if (currentStatus == STARTING || currentStatus == WIN || currentStatus == TIE) {
            printScore();
        }
    }
}

