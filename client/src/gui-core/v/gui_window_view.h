#pragma once

#include "gui_movable_container_view.h"

namespace Narradia
{
   class GuiWindowCloseButtonView;

   class GuiWindowView : public GuiMovableContainerView
   {
     public:
      GuiWindowView();

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
      std::shared_ptr<GuiWindowCloseButtonView> gui_window_close_button_view_;
   };
}
