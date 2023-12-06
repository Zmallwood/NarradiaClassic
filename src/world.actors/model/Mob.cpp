#include "Mob.h"

namespace Narradia {
    void Mob::Hit(float damage) {
        hp_ -= damage;
        ticks_last_hit_recieved_ = SDL_GetTicks();
    }

    bool Mob::IsDead() {
        return hp_ <= 0.0f;
    }
}
