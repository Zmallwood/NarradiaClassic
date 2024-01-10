#pragma once

namespace Narradia {
   class GuiComponentView;
   class SceneGui;

   class SceneGuiView {
     public:
      void Render();
      void AddGuiComponentView(SharedPtr<GuiComponentView> _compView);

      void SetSceneGui(SharedPtr<SceneGui> _value) {
         m_sceneGui = _value;
      }

     private:
      SharedPtr<SceneGui> m_sceneGui;
      Vec<SharedPtr<GuiComponentView>> m_guiComponentViews;
   };
}
