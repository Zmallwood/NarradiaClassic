#pragma once

namespace Narradia
{

   class CombatAdd : public S<CombatAdd>
   {
     public:
      void UpdateGameLogic();
   };

   class KbBindingsAdd : public S<KbBindingsAdd>
   {
     public:
      void UpdateGameLogic();
   };

   class MobDeathHandlingAdd : public S<MobDeathHandlingAdd>
   {
     public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningAdd : public S<PlayerSpawnPositioningAdd>
   {
     public:
      void SpawnAtGoodLocation();
   };
}
