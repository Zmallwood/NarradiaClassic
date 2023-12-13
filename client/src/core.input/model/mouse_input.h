#pragma once
#include "mouse_button.h"
#include <memory>
#include <SDL2/SDL.h>
namespace Narradia
{
    /**
     Contains the left and right mouse buttons and forwards
     function calls to the buttons.
    */
    class MouseInput : public Singleton<MouseInput> {
      public:
        MouseInput();
        void OnPress(Uint8 button);
        void OnRelease(Uint8 button);
        void PerformMouseActions();

        auto left_btn() {
            return left_btn_;
        }

        auto right_btn() {
            return right_btn_;
        }
      private:
        std::shared_ptr<MouseButton> left_btn_;
        std::shared_ptr<MouseButton> right_btn_;
    };
}
