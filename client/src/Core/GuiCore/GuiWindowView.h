#pragma once

#include "GuiMovableContainerView.h"

namespace Narradia {
   class GuiWindowCloseButtonV;

   class GuiWindowV : public GuiMovableContainerView {
     public:
      GuiWindowV();

      auto gui_window_close_button_view() {
         return gui_window_close_button_view_;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID rid_background_;
      RenderID rid_title_bar_;
      RenderID rid_title_text_;
      SharedPtr<GuiWindowCloseButtonV> gui_window_close_button_view_;
   };
}
