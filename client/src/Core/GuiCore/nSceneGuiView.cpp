#include "nSceneGuiView.h"
#include "nGuiComponentView.h"
#include "nSceneGui.h"

namespace Narradia {
   void nSceneGuiView::Render() {
      for (auto _guiComponentView : m_guiComponentViews)
         _guiComponentView->Render();
   }

   void nSceneGuiView::AddGuiComponentView(SharedPtr<nGuiComponentView> _compView) {
      auto _compModel = m_sceneGui->GuiComponents()->at(m_guiComponentViews.size());
      _compView->SetGuiComponent(_compModel);
      m_guiComponentViews.push_back(_compView);
   }
}
