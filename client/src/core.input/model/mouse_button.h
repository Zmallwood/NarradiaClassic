#pragma once
#include "mouse_action_mngr.h"
#include <functional>
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Holds state of a single mouse button, left or right, and its action manager which
   /// handles and executes mouse actions.
   ////////////////////////////////////////////////////////////////////////////////
   class MouseButton {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create internal structure.
      ////////////////////////////////////////////////////////////////////////////////
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>()) {
      }

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Called when the button has been pressed down.
      ////////////////////////////////////////////////////////////////////////////////
      auto OnPress() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Called when the button has been released.
      ////////////////////////////////////////////////////////////////////////////////
      auto OnRelease() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Executes a fired action and a released action, the ones with the highest z orders.
      ////////////////////////////////////////////////////////////////////////////////
      auto ExecMouseActions() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Add a new fired action.
      ///
      /// @param[in] action Function to execute if action is later executed.
      /// @param[in] z_order The canvas depth in which the clicked object is positioned.
      ////////////////////////////////////////////////////////////////////////////////
      auto AddFiredAction(std::function<void()> action, int z_order = 0) -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Add a new released action.
      ///
      /// @param[in] action Function to execute if action is later executed.
      /// @param[in] z_order The canvas depth in which the clicked object is positioned.
      ////////////////////////////////////////////////////////////////////////////////
      auto AddReleasedAction(std::function<void()> action, int z_order = 0) -> void;

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
