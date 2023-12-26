#include "mouse_input.h"
namespace Narradia
{
   auto MouseInput::OnPress(Uint8 button) -> void
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnPress();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnPress();
         break;
      }
   }

   auto MouseInput::OnRelease(Uint8 button) -> void
   {
      switch (button)
      {
      case SDL_BUTTON_LEFT:
         left_btn_->OnRelease();
         break;
      case SDL_BUTTON_RIGHT:
         right_btn_->OnRelease();
         break;
      }
   }

   auto MouseInput::ExecMouseActions() -> void
   {
      left_btn_->ExecMouseActions();
      right_btn_->ExecMouseActions();
   }
}
