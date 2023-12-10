#include "mob.h"

namespace Narradia {
  /**
   Hit mob with damage.
  */
  void Mob::Hit(float damage) {
    hp_ -= damage;
    ticks_last_hit_recieved_ = SDL_GetTicks();
  }

  /**
   Is mob dead.
  */
  bool Mob::IsDead() {
    return hp_ <= 0.0f;
  }
}
