#pragma once

#include "nGuiComponentView.h"

namespace Narradia {
   class GuiContainer;

   class GuiContainerView : public GuiComponentView {
     protected:
      void Render() override;
      void AddGuiComponentView(SharedPtr<GuiComponentView> _compView);

      void SetGuiContainer(SharedPtr<GuiContainer> _value) {
         m_guiContainer = _value;
      }

     private:
      SharedPtr<GuiContainer> m_guiContainer;
      Vec<SharedPtr<GuiComponentView>> m_guiComponentViews;
   };
}
