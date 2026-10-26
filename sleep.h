#ifndef __SLEEPING__
#define __SLEEPING__

#include "proj_utils.h"
#include "int_handlers.h"

namespace SleepHandler {
  bool isDeepSleep();
  void checkInactivity();
}

#endif