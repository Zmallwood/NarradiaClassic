#include "mob.h"
namespace Narradia
{
   /**
    Hit mob with damage.
   */
   void Mob::Hit(float damage) {
      health_ -= damage;
      ticks_last_hit_recieved_ = SDL_GetTicks();
      aggroing_player_ = true;
   }

   /**
    Is mob dead.
   */
   bool Mob::IsDead() {
      return health_ <= 0.0f;
   }

   void Mob::AggroPlayer() {
      aggroing_player_ = true;
   }
}
