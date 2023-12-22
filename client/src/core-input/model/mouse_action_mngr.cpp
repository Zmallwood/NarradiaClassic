#include "mouse_action_mngr.h"
namespace Narradia
{
   auto MouseActionMngr::AddFiredAction(std::function<void()> action, int z_order) -> void {
      fired_actions_.push_back({action, z_order});
   }

   auto MouseActionMngr::AddReleasedAction(std::function<void()> action, int z_order) -> void {
      released_actions_.push_back({action, z_order});
   }

   auto MouseActionMngr::ExecFiredActions() -> bool {
      if (fired_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : fired_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order) {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }

   auto MouseActionMngr::ExecReleasedActions() -> bool {
      if (released_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : released_actions_) {
         if (action.z_order > top_most_z_order) {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order) {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }

   auto MouseActionMngr::ClearFiredActions() -> void {
      fired_actions_.clear();
   }

   auto MouseActionMngr::ClearReleasedActions() -> void {
      released_actions_.clear();
   }
}
