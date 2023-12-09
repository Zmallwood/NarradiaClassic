#pragma once
#include "MouseActionMngr.h"

namespace Narradia {
    /**
     Holds state of a single mouse button, left or right, and its
     MouseActionMngr which handle and execute mouse actions.
    */
    class MouseButton {
      public:
        MouseButton()
            : mouse_action_mngr_(std::make_shared<MouseActionMngr>()) {
        }
        void RegisterPress();
        void RegisterRelease();
        void PerformMouseActions();
        void AddFiredAction(std::function<void()> action, int z_level = 0);
        void AddReleasedAction(std::function<void()> action, int z_level = 0);

        bool is_pressed() {
            return is_pressed_;
        }

        std::shared_ptr<MouseActionMngr> mouse_action_mngr() {
            return mouse_action_mngr_;
        }

      private:
        bool is_pressed_ = false;
        bool has_been_fired_ = false;
        bool has_been_released_ = false;
        std::shared_ptr<MouseActionMngr> mouse_action_mngr_;
    };
}
