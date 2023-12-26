#pragma once
#include <memory>
namespace Narradia
{
   class GuiWindow;

   class GuiWindowCloseButton
   {
     public:
      GuiWindowCloseButton(std::shared_ptr<GuiWindow> parent_window)
          : parent_window_(parent_window)
      {
      }

      void UpdateGameLogic();

      auto hovered()
      {
         return hovered_;
      }

      RectF Bounds() const;

     private:
      static constexpr float kWidth = 0.01f;
      std::shared_ptr<GuiWindow> parent_window_;
      bool hovered_ = false;
   };
}
