#pragma once
#include "mouse_button.h"
namespace Narradia
{
   class MouseInput : public Singleton<MouseInput>
   {
     public:
      MouseInput()
          : left_btn_(std::make_shared<MouseButton>()),
            right_btn_(std::make_shared<MouseButton>())
      {
      }

      auto OnPress(Uint8 button) -> void;

      auto OnRelease(Uint8 button) -> void;

      auto ExecMouseActions() -> void;

      auto left_btn()
      {
         return left_btn_;
      }

      auto right_btn()
      {
         return right_btn_;
      }

     private:
      std::shared_ptr<MouseButton> left_btn_;
      std::shared_ptr<MouseButton> right_btn_;
   };
}
