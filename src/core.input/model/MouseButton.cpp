#include "MouseButton.h"

namespace Narradia
{
    /**
     * Called from MouseInput when a mouse button has been pressed down.
     */
    void MouseButton::RegisterPress()
    {
        is_pressed_ = true;
        has_been_fired_ = true;
        has_been_released_ = false;
    }

    /**
     * Called from MouseInput when a mouse button has been released.
     */
    void MouseButton::RegisterRelease()
    {
        is_pressed_ = false;
        has_been_fired_ = false;
        has_been_released_ = true;
    }

    /**
     * Performs mouse actions, if any exist, for mouse click/release depending
     * on the z orders of the actions.
     */
    void MouseButton::PerformMouseActions()
    {
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

    /**
     * Adds an action which might be executed on mouse down event, depending on
     * its z order.
     */
    void MouseButton::AddFiredAction(std::function<void()> action, int z_level)
    {
        mouse_action_mngr_->AddFiredAction(action, z_level);
    }

    /**
     * Adds an action which might be executed on mouse up event, depending on
     * its z order.
     */
    void MouseButton::AddReleasedAction(std::function<void()> action, int z_level)
    {
        mouse_action_mngr_->AddReleasedAction(action, z_level);
    }
}
