#pragma once

namespace Narradia
{
    // Show sub classes
#if 1
   class MouseAction
   {
     public:
      std::function<void()> action;
      int z_order = 0;
   };

   class MouseActionMngr
   {
     public:
      auto AddFiredAction(std::function<void()> action, int z_order = 0) -> void;

      auto AddReleasedAction(std::function<void()> action, int z_order = 0) -> void;

      auto ExecFiredActions() -> bool;

      auto ExecReleasedActions() -> bool;

      auto ClearFiredActions() -> void;

      auto ClearReleasedActions() -> void;

     private:
      std::vector<MouseAction> fired_actions_;
      std::vector<MouseAction> released_actions_;
   };

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
#endif

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
