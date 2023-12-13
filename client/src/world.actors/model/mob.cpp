#include "mob.h"
namespace Narradia
{
   /**
    Hit mob with damage.
   */
   void Mob::Hit(float damage) {
      health_ -= damage;
      ticks_last_hit_recieved_ = SDL_GetTicks();
   }

   /**
    Is mob dead.
   */
   bool Mob::IsDead() {
      return health_ <= 0.0f;
   }
}
