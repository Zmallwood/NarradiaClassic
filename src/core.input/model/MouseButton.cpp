#include "MouseButton.h"

namespace Narradia {
    void MouseButton::RegisterPress() {
        is_pressed_ = true;
        has_been_fired_ = true;
        has_been_released_ = false;
    }

    void MouseButton::RegisterRelease() {
        is_pressed_ = false;
        has_been_fired_ = false;
        has_been_released_ = true;
    }

    void MouseButton::PerformMouseActions() {
        if (has_been_fired_) {
            mouse_action_mngr_->PerformFiredActions();
        }

        mouse_action_mngr_->ClearFiredActions();
        has_been_fired_ = false;

        if (has_been_released_) {
            mouse_action_mngr_->PerformReleasedActions();
        }

        mouse_action_mngr_->ClearReleasedActions();
        has_been_released_ = false;
    }

    void
    MouseButton::AddFiredAction(std::function<void()> action, int z_level) {
        mouse_action_mngr_->AddFiredAction(action, z_level);
    }

    void
    MouseButton::AddReleasedAction(std::function<void()> action, int z_level) {
        mouse_action_mngr_->AddReleasedAction(action, z_level);
    }
}
