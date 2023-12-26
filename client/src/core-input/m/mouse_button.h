#pragma once
#include "mouse_action_mngr.h"
#include <functional>
#include <memory>
namespace Narradia
{
   class MouseButton
   {
     public:
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>())
      {
      }

      auto OnPress() -> void;

      auto OnRelease() -> void;

      auto ExecMouseActions() -> void;

      auto AddFiredAction(std::function<void()> action, int z_order = 0) -> void;

      auto AddReleasedAction(std::function<void()> action, int z_order = 0) -> void;

      auto is_pressed()
      {
         return is_pressed_;
      }

      auto action_mngr()
      {
         return action_mngr_;
      }

     private:
      bool is_pressed_ = false;
      bool has_been_fired_ = false;
      bool has_been_released_ = false;
      std::shared_ptr<MouseActionMngr> action_mngr_;
   };
}
