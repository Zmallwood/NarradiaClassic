#pragma once

namespace Narradia {
    class MouseButton {
      public:
        void RegisterPress();

        void RegisterRelease();

        bool HasBeenFiredPickResult();

        bool HasBeenReleasedPickResult();

        bool is_pressed() {
            return is_pressed_;
        }

      private:
        bool is_pressed_ = false;
        bool has_been_fired_ = false;
        bool has_been_released_ = false;
    };
}