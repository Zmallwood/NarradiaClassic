#include "GuiWindowCloseButtonView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "GuiWindowCloseButton.h"

namespace Narradia {
   GuiWindowCloseButtonView::GuiWindowCloseButtonView() {
      m_RIDCloseButtonImg = NewImage();
   }
   void GuiWindowCloseButtonView::Render() {
      if (m_model->GetHovered())
         DrawImage("GuiWindowCloseButtonHovered", m_RIDCloseButtonImg, m_model->Bounds());
      else
         DrawImage("GuiWindowCloseButton", m_RIDCloseButtonImg, m_model->Bounds());
   }
}
