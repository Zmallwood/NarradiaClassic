#include "gui_window.h"
namespace Narradia
{
   GuiWindow::GuiWindow(
       std::string_view title, RectF bounds, bool destroy_on_close,
       std::string_view background_image_name)
       : GuiMovableContainer(
             {0.0f, 0.0f, bounds.w, kTitleBarHeight}, bounds.GetPosition(), bounds.GetSize()),
         gui_window_close_button_(
             std::make_shared<GuiWindowCloseButton>(std::shared_ptr<GuiWindow>(this)))
   {
      background_image_name_ = background_image_name;
      title_ = title;
      destroy_on_close_ = destroy_on_close;
   }

   void GuiWindow::Hide()
   {
      visible_ = false;
   }

   void GuiWindow::ToggleVisibility()
   {
      visible_ = !visible_;
   }

   void GuiWindow::UpdateGameLogic()
   {
      if (!visible_)
         return;
      gui_window_close_button_->UpdateGameLogic();
      UpdateGameLogicDerived();
      GuiMovableContainer::UpdateGameLogic();
   }

   RectF GuiWindow::AbsTitleBarBounds()
   {
      return {position().x, position().y, size().w, kTitleBarHeight};
   }
}
