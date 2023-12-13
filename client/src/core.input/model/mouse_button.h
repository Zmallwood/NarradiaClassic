#pragma once
#include "mouse_action_mngr.h"
#include <functional>
#include <memory>
namespace Narradia
{
   /**
    Holds state of a single mouse button, left or right,
    and its MouseActionMngr which handle and execute mouse
    actions.
   */
   class MouseButton {
     public:
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>()) {
      }
      void OnPress();
      void OnRelease();
      void PerformMouseActions();
      void AddFiredAction(std::function<void()> action, int z_level = 0);
      void AddReleasedAction(std::function<void()> action, int z_level = 0);

      auto is_pressed() {
         return is_pressed_;
      }

      auto action_mngr() {
         return action_mngr_;
      }

     private:
      bool is_pressed_ = false;
      bool has_been_fired_ = false;
      bool has_been_released_ = false;
      std::shared_ptr<MouseActionMngr> action_mngr_;
   };
}
