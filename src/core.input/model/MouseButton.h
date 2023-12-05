#pragma once
#include "MouseActionMngr.h"

namespace Narradia {
    class MouseButton {
      public:
        MouseButton()
            : mouse_action_mngr_(std::make_shared<MouseActionMngr>()) {
        }

        void RegisterPress();

        void RegisterRelease();

        bool HasBeenFiredPickResult();

        bool HasBeenReleasedPickResult();

        void PerformMouseActions();

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
