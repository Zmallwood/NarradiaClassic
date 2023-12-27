#pragma once

namespace Narradia
{
   class FPSCapper : public S<FPSCapper>
   {
     public:
      auto Below60FPS() -> bool;

     private:
      int prev_ticks_ = 0;
   };
}
