#pragma once

namespace Narradia
{
   class KbBindingsAdd : public S<KbBindingsAdd> {
     public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningAdd : public S<PlayerSpawnPositioningAdd> {
     public:
      void SpawnAtGoodLocation();
   };
}
