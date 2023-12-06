#include "MouseInput.h"

namespace Narradia {
    MouseInput::MouseInput()
        : left_button_(std::make_shared<MouseButton>()),
          right_button_(std::make_shared<MouseButton>()) {
    }

    void MouseInput::Reset() {
        left_button_->Reset();
        right_button_->Reset();
        ClearMouseActions();
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

    bool MouseInput::AnyButtonBeenFiredPickResult() {
        auto left = left_button_->HasBeenFiredPickResult();
        auto right = left_button_->HasBeenFiredPickResult();

        return left | right;
    }

    void MouseInput::ClearMouseActions() {
        left_button_->mouse_action_mngr()->ClearActions();
        right_button_->mouse_action_mngr()->ClearActions();
    }

    void MouseInput::PerformMouseActions() {
        left_button_->PerformMouseActions();
        right_button_->PerformMouseActions();
    }
}