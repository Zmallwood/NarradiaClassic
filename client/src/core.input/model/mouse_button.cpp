#include "mouse_button.h"
namespace Narradia
{
   auto MouseButton::OnPress() -> void {
      is_pressed_ = true;
      has_been_fired_ = true;
      has_been_released_ = false;
   }

   auto MouseButton::OnRelease() -> void {
      is_pressed_ = false;
      has_been_fired_ = false;
      has_been_released_ = true;
   }

   auto MouseButton::ExecMouseActions() -> void {
      if (has_been_fired_) {
         action_mngr_->ExecFiredActions();
      }
      action_mngr_->ClearFiredActions();
      has_been_fired_ = false;
      if (has_been_released_) {
         action_mngr_->ExecReleasedActions();
      }
      action_mngr_->ClearReleasedActions();
      has_been_released_ = false;
   }

   auto MouseButton::AddFiredAction(std::function<void()> action, int z_order) -> void {
      action_mngr_->AddFiredAction(action, z_order);
   }

   auto MouseButton::AddReleasedAction(std::function<void()> action, int z_order) -> void {
      action_mngr_->AddReleasedAction(action, z_order);
   }
}
