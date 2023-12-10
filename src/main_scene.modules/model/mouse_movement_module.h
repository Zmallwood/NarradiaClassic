#pragma once

namespace Narradia {
  class MouseMovementModule : public Singleton<MouseMovementModule> {
   public:
    void UpdateGameLogic();
  };
}
