#include "nGuiContainer.h"

namespace Narradia {
   void nGuiContainer::UpdateGameLogic() {
      for (auto &_comp : *m_guiComponents)
         _comp->UpdateGameLogic();
   }

   void nGuiContainer::AddGuiComponent(SharedPtr<nGuiComponent> _comp) {
      m_guiComponents->push_back(_comp);
   }

   RectF nGuiContainer::Bounds() {
      return {m_pos.x, m_pos.y, m_size.w, m_size.h};
   }
}
