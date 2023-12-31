#pragma once

namespace Narradia
{
   // Model
   #if 1
   class KbBindingsAdd : public S<KbBindingsAdd> {
     public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningAdd : public S<PlayerSpawnPositioningAdd> {
     public:
      void SpawnAtGoodLocation();
   };
#endif
}
