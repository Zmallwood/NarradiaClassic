#pragma once

namespace Narradia {
  class MobDeathHandlingModule : public Singleton<MobDeathHandlingModule> {
   public:
    void UpdateGameLogic();
  };
}
