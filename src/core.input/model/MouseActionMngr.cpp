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

    bool MouseActionMngr::PerformFiredActions() {
        if (fired_actions_.size() == 0)
            return false;
        
        MouseAction top_most_action = {[] {}, -1};

        for (auto action : fired_actions_) {
            if (action.z_level > top_most_action.z_level)
                top_most_action = action;
        }

        top_most_action.action();

        return true;
    }

    bool MouseActionMngr::PerformReleasedActions() {
        if (released_actions_.size() == 0)
            return false;

        MouseAction top_most_action = {[] {}, -1};

        for (auto action : released_actions_) {
            if (action.z_level > top_most_action.z_level)
                top_most_action = action;
        }

        top_most_action.action();

        return true;
    }

    void MouseActionMngr::ClearFiredActions() {
        fired_actions_.clear();
    }

    void MouseActionMngr::ClearReleasedActions() {

        released_actions_.clear();
    }
}
