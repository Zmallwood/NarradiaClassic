#include "mouse_input.h"

namespace Narradia
{
    // MouseInput
#if 1
   auto MouseInput::OnPress(Uint8 button) -> void
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnPress();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnPress();
         break;
      }
   }

   auto MouseInput::OnRelease(Uint8 button) -> void
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnRelease();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnRelease();
         break;
      }
   }

   auto MouseInput::ExecMouseActions() -> void
   {
      left_btn_->ExecMouseActions();
      right_btn_->ExecMouseActions();
   }
#endif

   // MouseButton
#if 1
   auto MouseButton::OnPress() -> void
   {
      is_pressed_ = true;
      has_been_fired_ = true;
      has_been_released_ = false;
   }

   auto MouseButton::OnRelease() -> void
   {
      is_pressed_ = false;
      has_been_fired_ = false;
      has_been_released_ = true;
   }

   auto MouseButton::ExecMouseActions() -> void
   {
      if (has_been_fired_)
      {
         action_mngr_->ExecFiredActions();
      }
      action_mngr_->ClearFiredActions();
      has_been_fired_ = false;
      if (has_been_released_)
      {
         action_mngr_->ExecReleasedActions();
      }
      action_mngr_->ClearReleasedActions();
      has_been_released_ = false;
   }

   auto MouseButton::AddFiredAction(std::function<void()> action, int z_order) -> void
   {
      action_mngr_->AddFiredAction(action, z_order);
   }

   auto MouseButton::AddReleasedAction(std::function<void()> action, int z_order) -> void
   {
      action_mngr_->AddReleasedAction(action, z_order);
   }
#endif

   // MouseActionMngr
#if 1
   auto MouseActionMngr::AddFiredAction(std::function<void()> action, int z_order) -> void
   {
      fired_actions_.push_back({action, z_order});
   }

   auto MouseActionMngr::AddReleasedAction(std::function<void()> action, int z_order) -> void
   {
      released_actions_.push_back({action, z_order});
   }

   auto MouseActionMngr::ExecFiredActions() -> bool
   {
      if (fired_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : fired_actions_)
      {
         if (action.z_order > top_most_z_order)
         {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order)
         {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }

   auto MouseActionMngr::ExecReleasedActions() -> bool
   {
      if (released_actions_.size() == 0)
         return false;
      int top_most_z_order = -1;
      std::vector<MouseAction> top_most_actions;
      for (auto action : released_actions_)
      {
         if (action.z_order > top_most_z_order)
         {
            top_most_actions.clear();
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
         else if (action.z_order == top_most_z_order)
         {
            top_most_actions.push_back(action);
            top_most_z_order = action.z_order;
         }
      }
      for (auto &action : top_most_actions)
         action.action();
      return true;
   }

   auto MouseActionMngr::ClearFiredActions() -> void
   {
      fired_actions_.clear();
   }

   auto MouseActionMngr::ClearReleasedActions() -> void
   {
      released_actions_.clear();
   }
#endif
}
