#pragma once

namespace Narradia {
  class WorldViewModule : public Singleton<WorldViewModule> {
   public:
    WorldViewModule();
    void UpdateGameLogic();
  };
}
