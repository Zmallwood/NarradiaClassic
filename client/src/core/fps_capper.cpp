#include "fps_capper.h"

namespace Narradia
{
   auto FPSCapper::Below60FPS() -> bool
   {
      auto curr_ticks = SDL_GetTicks();
      auto delta = curr_ticks - prev_ticks_;
      if (delta > 1000 / 60.0f)
      {
         prev_ticks_ = curr_ticks;
         return true;
      }
      return false;
   }
}
