#include "fps_capper.h"

namespace Narradia
{
   int curr_ticks, delta;

   auto FPSCapper::RunningBelow60FPS() -> bool
   {
      curr_ticks = SDL_GetTicks();
      delta = curr_ticks - prev_ticks_;
      if (delta > 1000 / 60.0f)
      {
         prev_ticks_ = curr_ticks;
         return true;
      }
      return false;
   }
}
