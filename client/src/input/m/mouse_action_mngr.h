#pragma once

#include "mouse_action.h"

namespace Narradia
{
   class MouseActionMngr
   {
     public:
      auto AddFiredAction(std::function<void()> action, int z_order = 0) -> void;

      auto AddReleasedAction(std::function<void()> action, int z_order = 0) -> void;

      auto ExecFiredActions() -> bool;

      auto ExecReleasedActions() -> bool;

      auto ClearFiredActions() -> void;

      auto ClearReleasedActions() -> void;

     private:
      std::vector<MouseAction> fired_actions_;
      std::vector<MouseAction> released_actions_;
   };
}
