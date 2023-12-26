#include "gui_button.h"
namespace Narradia
{
   GuiButton::GuiButton(
       const std::string_view &text, RectF bounds, std::function<void()> action,
       std::string_view img_name, std::string_view hovered_img_name)
   {
      text_ = text;
      bounds_ = bounds;
      action_ = action;
      img_name_ = img_name;
      hovered_img_name_ = hovered_img_name;
   }

   auto GuiButton::UpdateGameLogic() -> void
   {
      hovered_ = false;
      auto used_bounds = bounds_;
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      if (used_bounds.Contains(MousePosition()))
      {
         Cursor::get()->set_style(CursorStyles::Hovering);
         hovered_ = true;
         MouseInput::get()->left_btn()->AddFiredAction([&] { action_(); }, 2);
      }
   }
}
