#pragma once

#include "nGuiComponentView.h"

namespace Narradia {
   class nGuiContainer;

   class nGuiContainerView : public nGuiComponentView {
     protected:
      void Render() override;
      void AddGuiComponentView(SharedPtr<nGuiComponentView> _compView);

      void SetGuiContainer(SharedPtr<nGuiContainer> _value) {
         m_guiContainer = _value;
      }

     private:
      SharedPtr<nGuiContainer> m_guiContainer;
      Vec<SharedPtr<nGuiComponentView>> m_guiComponentViews;
   };
}
