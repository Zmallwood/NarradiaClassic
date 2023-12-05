#pragma once
#include "MouseButton.h"

namespace Narradia {
    class MouseInput : public Singleton<MouseInput> {
      public:
        MouseInput();

        void Reset();

        void RegisterPress(Uint8 button);

        void RegisterRelease(Uint8 button);

        bool AnyButtonBeenFiredPickResult();

        void PerformMouseActions();

        std::shared_ptr<MouseButton> left_button() {
            return left_button_;
        }

        std::shared_ptr<MouseButton> right_button() {
            return right_button_;
        }

      private:
        void ClearMouseActions();

        std::shared_ptr<MouseButton> left_button_;
        std::shared_ptr<MouseButton> right_button_;
    };
}
