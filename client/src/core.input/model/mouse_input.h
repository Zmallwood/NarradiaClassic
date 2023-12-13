#pragma once
#include "mouse_button.h"
#include <SDL2/SDL.h>
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Contains the left and right mouse buttons and forwards function calls to them.
   ////////////////////////////////////////////////////////////////////////////////
   class MouseInput : public Singleton<MouseInput> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create the left and right mouse buttons.
      ////////////////////////////////////////////////////////////////////////////////
      MouseInput()
          : left_btn_(std::make_shared<MouseButton>()),
            right_btn_(std::make_shared<MouseButton>()) {
      }

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwards the press event to the correct mouse button.
      ///
      /// @param[in] button Mouse button that has been pressed.
      ////////////////////////////////////////////////////////////////////////////////
      auto OnPress(Uint8 button) -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwards the release event to the correct mouse button.
      ///
      /// @param[in] button Mouse button that has been released.
      ////////////////////////////////////////////////////////////////////////////////
      auto OnRelease(Uint8 button) -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Performs the mouse actions for both mouse buttons.
      ////////////////////////////////////////////////////////////////////////////////
      auto ExecMouseActions() -> void;

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
