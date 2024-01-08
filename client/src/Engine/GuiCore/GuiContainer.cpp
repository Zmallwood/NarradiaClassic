#include "GuiContainer.h"

namespace Narradia {
   void GuiContainer::UpdateGameLogic() {
      for (auto &_comp : *m_guiComponents)
         _comp->UpdateGameLogic();
   }
   void GuiContainer::AddGuiComponent(SharedPtr<GuiComponent> _comp) {
      m_guiComponents->push_back(_comp);
   }
   RectF GuiContainer::Bounds() {
      return {m_pos.x, m_pos.y, m_size.w, m_size.h};
   }
}
