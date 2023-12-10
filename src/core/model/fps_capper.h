#pragma once

namespace Narradia {
  class FPSCapper : public Singleton<FPSCapper> {
   public:
    bool RunningBelow60FPS();

   private:
    int prev_ticks_ = 0;
  };
}
