#include "nSceneGuiView.h"
#include "nGuiComponentView.h"
#include "nSceneGui.h"

namespace Narradia {
   void SceneGuiView::Render() {
      for (auto _guiComponentView : m_guiComponentViews)
         _guiComponentView->Render();
   }

   void SceneGuiView::AddGuiComponentView(SharedPtr<GuiComponentView> _compView) {
      auto _compModel = m_sceneGui->GetGuiComponents()->at(m_guiComponentViews.size());
      _compView->SetGuiComponent(_compModel);
      m_guiComponentViews.push_back(_compView);
   }
}
