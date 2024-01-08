#include "GuiMovableContainer.h"

namespace Narradia {
   void GuiMovableContainer::UpdateGameLogic() {
      auto _mousePos = MousePos();
      auto _absDragableArea = m_relDragableArea.Translate(GetPos().x, GetPos().y);
      if (_absDragableArea.Contains(_mousePos)) {
         if (!m_isMoving && !m_movementTrigger) {
            MouseInput::get()->left_btn()->AddFiredAction(
                [&] {
                   m_selfPosStartMoving = GetPos();
                   m_mousePosStartMoving = MousePos();
                   m_isMoving = true;
                },
                SDL_GetTicks());
         }
      }
      if (m_isMoving) {
         auto _dx = _mousePos.x - m_mousePosStartMoving.x;
         auto _dy = _mousePos.y - m_mousePosStartMoving.y;
         SetPos({m_selfPosStartMoving.x + _dx, m_selfPosStartMoving.y + _dy});
         m_movementTrigger = true;
         MouseInput::get()->left_btn()->AddReleasedAction(
             [&] {
                m_isMoving = false;
                m_movementTrigger = false;
             },
             SDL_GetTicks());
      }
      GuiContainer::UpdateGameLogic();
   }
}
