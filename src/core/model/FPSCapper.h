#pragma once

namespace Narradia {
    class FPSCapper : public Singleton<FPSCapper> {
      public:
        bool RunningBelow60FPS();

      private:
        int b_ = 0;
    };
}
