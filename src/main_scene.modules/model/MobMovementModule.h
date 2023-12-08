#pragma once

namespace Narradia {

    class MobMovementModule : public Singleton<MobMovementModule> {
      public:
        void UpdateGameLogic();
    };
}
