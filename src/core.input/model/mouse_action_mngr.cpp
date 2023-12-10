#include "mouse_action_mngr.h"

namespace Narradia {
  /**
   Adds an action which might be executed on firing the
   mouse button, depending on its z order.
  */
  void MouseActionMngr::AddFiredAction(std::function<void()> action, int z_level) {
    fired_actions_.push_back({action, z_level});
  }

  /**
   Adds an action which might be executed on releasing the
   mouse button, depending on its z order.
  */
  void MouseActionMngr::AddReleasedAction(std::function<void()> action, int z_level) {
    released_actions_.push_back({action, z_level});
  }

  /**
   Perform the fired-action with the highest z order.
  */
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

  /**
   Perform the released-action with the highest z order.
  */
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

  /**
   Clear all fired-actions.
  */
  void MouseActionMngr::ClearFiredActions() {
    fired_actions_.clear();
  }

  /**
   Clear all released-actions.
  */
  void MouseActionMngr::ClearReleasedActions() {
    released_actions_.clear();
  }
}
