#pragma once

namespace Narradia {
   class nGuiComponent;

   class nSceneGui {
     public:
      nSceneGui()
          : m_guiComponents(MakeShared<Vec<SharedPtr<nGuiComponent>>>()) {
      }
      void UpdateGameLogic();
      void AddGuiComponent(SharedPtr<nGuiComponent> _comp);
      void RemoveGuiComponent(nGuiComponent *_comp);

      auto GuiComponents() {
         return m_guiComponents;
      }

     private:
      SharedPtr<Vec<SharedPtr<nGuiComponent>>> m_guiComponents;
   };
}
