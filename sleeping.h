#ifndef __PROJSLEEP__
#define __PROJSLEEP__

#include <avr/sleep.h>
#include <TimerOne.h>
#include "proj_constants.h"
#include "display.h"
#include "engine.h"

namespace Sleeping {
  void manageDeepSleep(); // Manages the deep sleeping when invoked
}

#endif