#pragma once
namespace Narradia {
  class CombatModule : public Singleton<CombatModule> {
   public:
    void UpdateGameLogic();
  };
}
