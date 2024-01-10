#include "nGuiContainerView.h"
#include "nGuiContainer.h"

namespace Narradia {
   void nGuiContainerView::Render() {
      for (auto &_compView : m_guiComponentViews)
         _compView->Render();
   }

   void nGuiContainerView::AddGuiComponentView(SharedPtr<nGuiComponentView> _compView) {
      auto _compModel = m_guiContainer->GuiComponents()->at(m_guiComponentViews.size());
      _compView->SetGuiComponent(_compModel);
      m_guiComponentViews.push_back(_compView);
   }
}
