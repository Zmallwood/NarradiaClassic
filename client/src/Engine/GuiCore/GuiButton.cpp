#include "GuiButton.h"

namespace Narradia {
   // clang-format off
   GuiButton::GuiButton(
      const StringView &_text,
      RectF _bounds,
      Function<void()> _action,
      StringView _imgName,
      StringView _hoveredImgName) {
      // clang-format on
      m_text = _text;
      m_bounds = _bounds;
      m_action = _action;
      m_imgName = _imgName;
      m_hoveredImgName = _hoveredImgName;
   }

   void GuiButton::UpdateGameLogic() {
      m_hovered = false;
      auto _usedBounds = m_bounds;

      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }

      if (_usedBounds.Contains(MousePos())) {
         Cursor::get()->set_style(CursorStyles::Hovering);
         m_hovered = true;
         MouseInput::get()->left_btn()->AddFiredAction([&] { m_action(); }, 2);
      }
   }
}
