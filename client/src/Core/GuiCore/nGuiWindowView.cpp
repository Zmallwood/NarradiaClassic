#include "nGuiWindowView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "nGuiWindow.h"
#include "nGuiWindowCloseButtonView.h"

namespace Narradia {
   nGuiWindowView::nGuiWindowView()
       : m_guiWindowCloseButtonView(MakeShared<nGuiWindowCloseButtonView>()) {
      m_RIDBackground = NewImage();
      m_RIDTitleBar = NewImage();
      m_RIDTitleText = NewString();
   }

   void nGuiWindowView::Render() {
      auto _model = static_pointer_cast<nGuiWindow>(m_guiComponent);
      if (!_model->Visible())
         return;
      DrawImage(_model->BgImageName(), m_RIDBackground, _model->Bounds());
      DrawImage("GuiWindowTitleBar", m_RIDTitleBar, _model->AbsTitleBarBounds());
      m_guiWindowCloseButtonView->Render();
      DrawString(
          m_RIDTitleText, _model->Title(),
          _model->Bounds().GetPosition().Translate(0.005f, 0.01f));
      RenderDerived();
      nGuiMovableContainerView::Render();
   }
}
