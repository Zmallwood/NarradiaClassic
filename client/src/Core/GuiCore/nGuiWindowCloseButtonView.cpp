#include "nGuiWindowCloseButtonView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "nGuiWindowCloseButton.h"

namespace Narradia {
   nGuiWindowCloseButtonView::nGuiWindowCloseButtonView() {
      m_RIDCloseButtonImg = NewImage();
   }

   void nGuiWindowCloseButtonView::Render() {
      if (m_model->Hovered())
         DrawImage("GuiWindowCloseButtonHovered", m_RIDCloseButtonImg, m_model->Bounds());
      else
         DrawImage("GuiWindowCloseButton", m_RIDCloseButtonImg, m_model->Bounds());
   }
}
