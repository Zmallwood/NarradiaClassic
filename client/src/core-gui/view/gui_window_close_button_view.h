#pragma once
#include "../model/gui_window_close_button.h"
namespace Narradia
{
   class GuiWindowCloseButtonView {
     public:
      GuiWindowCloseButtonView();

      void Render();

      void set_model(std::shared_ptr<GuiWindowCloseButton> value) {
         model_ = value;
      }

     private:
      std::shared_ptr<GuiWindowCloseButton> model_;
      RenderID rid_close_btn_img_;
   };
}
