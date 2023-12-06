#include "MouseInput.h"

namespace Narradia {
    MouseInput::MouseInput()
        : left_button_(std::make_shared<MouseButton>()),
          right_button_(std::make_shared<MouseButton>()) {
    }

    void MouseInput::RegisterPress(Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_button_->RegisterPress();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->RegisterPress();
            break;
        }
    }

    void MouseInput::RegisterRelease(Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_button_->RegisterRelease();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->RegisterRelease();
            break;
        }
    }

    void MouseInput::PerformMouseActions() {
        left_button_->PerformMouseActions();
        right_button_->PerformMouseActions();
    }
}
