#pragma once

namespace Narradia
{
   // Show MouseButton
#if 1
   // Show MouseActionMngr
#if 1
   // Show MouseAction
#if 1
   class MouseAction
   {
     public:
      std::function<void()> action;
      int z_order = 0;
   };
#endif

   class MouseActionMngr
   {
     public:
      void AddFiredAction(std::function<void()> action, int z_order = 0);
      void AddReleasedAction(std::function<void()> action, int z_order = 0);
      bool ExecFiredActions();
      bool ExecReleasedActions();
      void ClearFiredActions();
      void ClearReleasedActions();

     private:
      std::vector<MouseAction> fired_actions_;
      std::vector<MouseAction> released_actions_;
   };
#endif

   class MouseButton
   {
     public:
      MouseButton()
          : action_mngr_(std::make_shared<MouseActionMngr>())
      {
      }

      void OnPress();
      void OnRelease();
      void ExecMouseActions();
      void AddFiredAction(std::function<void()> action, int z_order = 0);
      void AddReleasedAction(std::function<void()> action, int z_order = 0);
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

   class MouseInput : public S<MouseInput>
   {
     public:
      MouseInput()
          : left_btn_(std::make_shared<MouseButton>()),
            right_btn_(std::make_shared<MouseButton>())
      {
      }
      void OnPress(Uint8 button);
      void OnRelease(Uint8 button);
      void ExecMouseActions();
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
