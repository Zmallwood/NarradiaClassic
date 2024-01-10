#pragma once

namespace Narradia {
   class nGuiComponentView;
   class nSceneGui;

   class nSceneGuiView {
     public:
      void Render();
      void AddGuiComponentView(SharedPtr<nGuiComponentView> _compView);

      void SetSceneGui(SharedPtr<nSceneGui> _value) {
         m_sceneGui = _value;
      }

     private:
      SharedPtr<nSceneGui> m_sceneGui;
      Vec<SharedPtr<nGuiComponentView>> m_guiComponentViews;
   };
}
