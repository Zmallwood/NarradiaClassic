#pragma once

namespace Narradia {
   class GuiComponent;

   class SceneGui {
     public:
      SceneGui()
          : m_guiComponents(MakeShared<Vec<SharedPtr<GuiComponent>>>()) {
      }
      void UpdateGameLogic();
      void AddGuiComponent(SharedPtr<GuiComponent> _comp);
      void RemoveGuiComponent(GuiComponent *_comp);

      auto GetGuiComponents() {
         return m_guiComponents;
      }

     private:
      SharedPtr<Vec<SharedPtr<GuiComponent>>> m_guiComponents;
   };
}
