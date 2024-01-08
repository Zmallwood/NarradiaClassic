#pragma once

#include "GuiMovableContainerView.h"

namespace Narradia {
   class GuiWindowCloseButtonView;

   class GuiWindowView : public GuiMovableContainerView {
     public:
      GuiWindowView();

      auto GetGuiWindowCloseButtonView() {
         return m_guiWindowCloseButtonView;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID m_RIDBackground;
      RenderID m_RIDTitleBar;
      RenderID m_RIDTitleText;
      SharedPtr<GuiWindowCloseButtonView> m_guiWindowCloseButtonView;
   };
}
