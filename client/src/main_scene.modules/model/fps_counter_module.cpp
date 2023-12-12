#include "fps_counter_module.h"
namespace Narradia
{
    void FPSCounterModule::UpdateGameLogic() {
        frames_count_++;
        if (SDL_GetTicks() - ticks_last_update_ > kMillisPerSecond) {
            fps_ = frames_count_;
            frames_count_ = 0;
            ticks_last_update_ = SDL_GetTicks();
        }
    }
}
