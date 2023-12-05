#include "MouseActionMngr.h"

namespace Narradia {
    void
    MouseActionMngr::AddFiredAction(std::function<void()> action, int z_level) {
        fired_actions_.push_back({action, z_level});
    }

    void MouseActionMngr::AddReleasedAction(
        std::function<void()> action, int z_level) {
        released_actions_.push_back({action, z_level});
    }

    void MouseActionMngr::ClearActions() {
        fired_actions_.clear();
        released_actions_.clear();
    }

    void MouseActionMngr::PerformActions() {
        PerformFiredActions();
        PerformReleasedActions();
    }

    void MouseActionMngr::PerformFiredActions() {
        MouseAction top_most_action = {[] {}, -1};

        for (auto action : fired_actions_) {
            if (action.z_level > top_most_action.z_level)
                top_most_action = action;
        }

        top_most_action.action();
    }

    void MouseActionMngr::PerformReleasedActions() {
        MouseAction top_most_action = {[] {}, -1};

        for (auto action : released_actions_) {
            if (action.z_level > top_most_action.z_level)
                top_most_action = action;
        }

        top_most_action.action();
    }
}
