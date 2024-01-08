#pragma once

#include "GuiComponentView.h"

namespace Narradia {
   class GuiButtonView : public GuiComponentView {
     public:
      GuiButtonView();
      void Render() override;

     private:
      RenderID m_RIDImage;
      RenderID m_RIDLabelText;
   };
}
