#include "GuiWindowView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "GuiWindow.h"
#include "GuiWindowCloseButtonView.h"

namespace Narradia {
   GuiWindowView::GuiWindowView()
       : m_guiWindowCloseButtonView(MakeShared<GuiWindowCloseButtonView>()) {
      m_RIDBackground = NewImage();
      m_RIDTitleBar = NewImage();
      m_RIDTitleText = NewString();
   }
   void GuiWindowView::Render() {
      auto _model = static_pointer_cast<GuiWindow>(m_guiComponent);
      if (!_model->GetVisible())
         return;
      DrawImage(_model->GetBgImageName(), m_RIDBackground, _model->Bounds());
      DrawImage("GuiWindowTitleBar", m_RIDTitleBar, _model->AbsTitleBarBounds());
      m_guiWindowCloseButtonView->Render();
      DrawString(
          m_RIDTitleText, _model->GetTitle(),
          _model->Bounds().GetPosition().Translate(0.005f, 0.01f));
      RenderDerived();
      GuiMovableContainerView::Render();
   }
}
