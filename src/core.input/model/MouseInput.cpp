#include "MouseInput.h"

namespace Narradia
{
    /**
     Create the left and right mouse buttons.
    */
    MouseInput::MouseInput()
        : left_button_(std::make_shared<MouseButton>()),
          right_button_(std::make_shared<MouseButton>())
    {
    }

    /**
     Forwards the press register command to the correct mouse button.
    */
    void MouseInput::RegisterPress(Uint8 button)
    {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_button_->RegisterPress();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->RegisterPress();
            break;
        }
    }

    /**
     Forwards the release register command to the correct mouse button.
    */
    void MouseInput::RegisterRelease(Uint8 button)
    {
        switch (button) {
        case SDL_BUTTON_LEFT:
            left_button_->RegisterRelease();
            break;
        case SDL_BUTTON_RIGHT:
            right_button_->RegisterRelease();
            break;
        }
    }

    /**
     Perform mouse actions for both mouse buttons.
    */
    void MouseInput::PerformMouseActions()
    {
        left_button_->PerformMouseActions();
        right_button_->PerformMouseActions();
    }
}
