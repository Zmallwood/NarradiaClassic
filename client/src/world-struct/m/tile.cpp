#if 1
#include "tile.h"
#include "object.h"
#include "world-actors/m/mob.h"
#endif

namespace Narradia
{
   void Tile::IncreaseElevation(float amount)
   {
      elevation_ += amount;
   }
}
