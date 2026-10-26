#include "display.h"
#include "proj_utils.h"

constexpr int DISPLAY_X_SIZE { 20 };
constexpr int SCORE_DIGITS { 2 };

const String IDLE_TEXT = "Welcome to the React! Game. Press Buttons to Start    ";
const String STARTING_TEXT = "Go!";
const String WAITING_TEXT = "Ready...";
const String WIN_A_TEXT = "Ha vinto A!";
const String WIN_B_TEXT = "Ha vinto B!";
const String TIE_TEXT = "Pareggio!";
int currentChar {};

String getDisplayTextForStatus() {
    switch(currentStatus) {
        case IDLE:
            return IDLE_TEXT;
        case STARTING:
            return STARTING_TEXT;
        case WAITING:
            return WAITING_TEXT;
        case PLAYING:
            return String(toBePressed);
        case RESULT: {
            Game::RoundResult result = Game::getLastRoundResult();
            return (result == Game::TIE) ? TIE_TEXT :
                ((result == Game::WIN_A) ? WIN_A_TEXT : WIN_B_TEXT);
        }
        default:
            return "";
    }
}

String getLeadingSubString(const String& str, int startLen, int endLen) {
    int len = str.length();
    if (len == 0) {
        return "";
    }
    
    String result = "";
    for(int i = 0; i < endLen; i++) {
        int charIndex = (startLen + i) % len;
        result += str.charAt(charIndex);
    }
    return result;
}

void printScore() {
    lcd.setCursor(SCORE_DIGITS, 3);
    lcd.print(scoreA);
    lcd.setCursor(DISPLAY_X_SIZE - SCORE_DIGITS - 1, 3);
    lcd.print(scoreB);
}

namespace Display {
    void printRotating() {
        String displayed = getDisplayTextForStatus();
        String buffer = getLeadingSubString(displayed, currentChar, DISPLAY_X_SIZE);
        lcd.setCursor(0, 1);
        lcd.print(buffer);
        currentChar = (currentChar <= (int)displayed.length() ? (currentChar + 1) : 0);
        delay(50);
    }

    void normalPrint() {
        String displayed = getDisplayTextForStatus();
        lcd.setCursor(((DISPLAY_X_SIZE - (int)displayed.length() + 1) / 2), 1);
        lcd.print(displayed);
        if (currentStatus == STARTING || currentStatus == RESULT) {
            printScore();
        }
    }
}