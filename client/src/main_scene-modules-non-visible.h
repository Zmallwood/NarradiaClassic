#pragma once

namespace Narradia
{

   class CombatModule : public S<CombatModule>
   {
     public:
      void UpdateGameLogic();
   };

   class KbBindingsModule : public S<KbBindingsModule>
   {
     public:
      void UpdateGameLogic();
   };

   class MobDeathHandlingModule : public S<MobDeathHandlingModule>
   {
     public:
      void UpdateGameLogic();
   };

   class PlayerSpawnPositioningModule : public S<PlayerSpawnPositioningModule>
   {
     public:
      void SpawnAtGoodLocation();
   };
}
