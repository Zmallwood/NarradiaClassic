#pragma once
#include "MouseAction.h"

namespace Narradia
{
    /**
     * Adds and executes actions triggered by mouse click/release events,
     * depending on the z order of the object clicked with the mouse.
     */
    class MouseActionMngr {
      public:
        void AddFiredAction(std::function<void()> action, int z_level = 0);
        void AddReleasedAction(std::function<void()> action, int z_level = 0);
        bool PerformFiredActions();
        bool PerformReleasedActions();
        void ClearFiredActions();
        void ClearReleasedActions();

      private:
        std::vector<MouseAction> fired_actions_;
        std::vector<MouseAction> released_actions_;
    };
}
