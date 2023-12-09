#include "FPSCapper.h"

namespace Narradia {
    bool FPSCapper::RunningBelow60FPS() {
        auto a = SDL_GetTicks();
        auto delta = a - b_;

        if (delta > 1000 / 60.0f) {
            b_ = a;
            return true;
        }

        return false;
    }
}
