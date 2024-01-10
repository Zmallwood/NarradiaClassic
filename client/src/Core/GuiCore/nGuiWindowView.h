#pragma once

#include "nGuiMovableContainerView.h"

namespace Narradia {
   class nGuiWindowCloseButtonView;

   class nGuiWindowView : public nGuiMovableContainerView {
     public:
      nGuiWindowView();

      auto GuiWindowCloseButtonView() {
         return m_guiWindowCloseButtonView;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID m_RIDBackground;
      RenderID m_RIDTitleBar;
      RenderID m_RIDTitleText;
      SharedPtr<nGuiWindowCloseButtonView> m_guiWindowCloseButtonView;
   };
}
