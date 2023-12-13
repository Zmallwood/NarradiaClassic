#include "mouse_input.h"
namespace Narradia
{
    /**
     Create the left and right mouse buttons.
    */
    MouseInput::MouseInput()
        : left_btn_(std::make_shared<MouseButton>()),
          right_btn_(std::make_shared<MouseButton>()) {
    }

    /**
     Forwards the press register command to the correct
     mouse button.
    */
    void MouseInput::OnPress(Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_btn_->OnPress();
            break;
        case SDL_BUTTON_RIGHT:
            right_btn_->OnPress();
            break;
        }
    }

    /**
     Forwards the release register command to the correct
     mouse button.
    */
    void MouseInput::OnRelease(Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_btn_->OnRelease();
            break;
        case SDL_BUTTON_RIGHT:
            right_btn_->OnRelease();
            break;
        }
    }

    /**
     Perform mouse actions for both mouse buttons.
    */
    void MouseInput::PerformMouseActions() {
        left_btn_->PerformMouseActions();
        right_btn_->PerformMouseActions();
    }
}
