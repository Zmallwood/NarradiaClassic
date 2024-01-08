#include "SceneGui.h"
#include "GuiComponent.h"

namespace Narradia {
   void SceneGui::UpdateGameLogic() {
      for (auto _comp : *m_guiComponents)
         _comp->UpdateGameLogic();
   }
   void SceneGui::AddGuiComponent(SharedPtr<GuiComponent> _comp) {
      m_guiComponents->push_back(_comp);
   }
   void SceneGui::RemoveGuiComponent(GuiComponent *_comp) {
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
