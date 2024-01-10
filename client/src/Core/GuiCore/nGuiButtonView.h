#pragma once

#include "nGuiComponentView.h"

namespace Narradia {
   class nGuiButtonView : public nGuiComponentView {
     public:
      nGuiButtonView();
      void Render() override;

     private:
      RenderID m_RIDImage;
      RenderID m_RIDLabelText;
   };
}
