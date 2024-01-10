#include "nSceneGui.h"
#include "nGuiComponent.h"

namespace Narradia {
   void nSceneGui::UpdateGameLogic() {
      for (auto _comp : *m_guiComponents)
         _comp->UpdateGameLogic();
   }

   void nSceneGui::AddGuiComponent(SharedPtr<nGuiComponent> _comp) {
      m_guiComponents->push_back(_comp);
   }

   void nSceneGui::RemoveGuiComponent(nGuiComponent *_comp) {
      auto _i = 0;
      for (auto &_entry : *m_guiComponents) {
         if (_entry.get() == _comp) {
            m_guiComponents->erase(m_guiComponents->begin() + _i);
            break;
         }
         _i++;
      }
   }
}
