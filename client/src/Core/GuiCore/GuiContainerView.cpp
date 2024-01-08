#include "GuiContainerView.h"
#include "GuiContainer.h"

namespace Narradia {
   void GuiContainerView::Render() {
      for (auto &_compView : m_guiComponentViews)
         _compView->Render();
   }
   void GuiContainerView::AddGuiComponentView(SharedPtr<GuiComponentView> _compView) {
      auto _compModel = m_guiContainer->GetGuiComponents()->at(m_guiComponentViews.size());
      _compView->SetGuiComponent(_compModel);
      m_guiComponentViews.push_back(_compView);
   }
}
