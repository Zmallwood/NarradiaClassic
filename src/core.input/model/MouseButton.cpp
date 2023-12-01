#include "MouseButton.h"

namespace Narradia {
    void MouseButton::RegisterPress() {
        is_pressed_ = true;
        has_been_fired_ = true;
    }

    void MouseButton::RegisterRelease() {
        is_pressed_ = false;
        has_been_released_ = true;
    }

    bool MouseButton::HasBeenFiredPickResult() {
        auto result = has_been_fired_;
        has_been_fired_ = false;

        return result;
    }

    bool MouseButton::HasBeenReleasedPickResult() {
        auto result = has_been_released_;
        has_been_released_ = false;

        return result;
    }
}