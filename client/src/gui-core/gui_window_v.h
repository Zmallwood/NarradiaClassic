#pragma once

#include "gui_movable_container_v.h"

namespace Narradia
{
   class GuiWindowCloseButtonV;

   class GuiWindowV : public GuiMovableContainerV
   {
     public:
      GuiWindowV();
      auto gui_window_close_button_view()
      {
         return gui_window_close_button_view_;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID rid_background_;
      RenderID rid_title_bar_;
      RenderID rid_title_text_;
      std::shared_ptr<GuiWindowCloseButtonV> gui_window_close_button_view_;
   };
}
