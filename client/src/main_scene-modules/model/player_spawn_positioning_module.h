#pragma once
namespace Narradia
{
    class PlayerSpawnPositioningModule : public Singleton<PlayerSpawnPositioningModule> {
      public:
        void SpawnAtGoodLocation();
    };
}
