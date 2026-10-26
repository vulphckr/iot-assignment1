#ifndef __GAME__
#define __GAME__

#include "proj_utils.h"

namespace Game {
  typedef enum {
    WIN_A,
    WIN_B,
    TIE
  } RoundResult;

  void checkRoundResults();
  RoundResult getLastRoundResult();
  void resetScore();
  void resetPresses();
  void generatePresses();
  void generateT1();
}

#endif