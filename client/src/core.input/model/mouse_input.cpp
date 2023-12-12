#include "mouse_input.h"
namespace Narradia
{
    /**
     Create the left and right mouse buttons.
    */
    MouseInput::MouseInput()
        : left_button_(std::make_shared<MouseButton>()),
          right_button_(std::make_shared<MouseButton>()) {
    }

    /**
     Forwards the press register command to the correct
     mouse button.
    */
    void MouseInput::OnPress(Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_button_->OnPress();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->OnPress();
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
            left_button_->OnRelease();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->OnRelease();
            break;
        }
    }

    /**
     Perform mouse actions for both mouse buttons.
    */
    void MouseInput::PerformMouseActions() {
        left_button_->PerformMouseActions();
        right_button_->PerformMouseActions();
    }
}
