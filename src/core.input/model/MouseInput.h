#pragma once
#include "MouseButton.h"

namespace Narradia
{
    /**
     * Contains the left and right mouse buttons and forwards function calls to
     * the buttons.
     */
    class MouseInput : public Singleton<MouseInput> {
      public:
        MouseInput();
        void RegisterPress(Uint8 button);
        void RegisterRelease(Uint8 button);
        void PerformMouseActions();

        std::shared_ptr<MouseButton> left_button() {
            return left_button_;
        }

        std::shared_ptr<MouseButton> right_button() {
            return right_button_;
        }

      private:
        std::shared_ptr<MouseButton> left_button_;
        std::shared_ptr<MouseButton> right_button_;
    };
}
