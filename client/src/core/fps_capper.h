#pragma once

namespace Narradia
{
   class FPSCapper : public S<FPSCapper>
   {
     public:
      auto RunningBelow60FPS() -> bool;

     private:
      int prev_ticks_ = 0;
   };
}
