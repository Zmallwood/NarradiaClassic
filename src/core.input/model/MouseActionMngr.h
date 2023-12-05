#pragma once
#include "MouseAction.h"

namespace Narradia {
    class MouseActionMngr {
      public:
        void AddFiredAction(std::function<void()> action, int z_level);

        void AddReleasedAction(std::function<void()> action, int z_level);

        void ClearActions();

        void PerformActions();

        void PerformFiredActions();

        void PerformReleasedActions();

      private:
        std::vector<MouseAction> fired_actions_;
        std::vector<MouseAction> released_actions_;
    };
}
