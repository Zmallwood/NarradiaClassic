#pragma once

namespace Narradia
{
   class GuiWindowCloseButton;

   class GuiWindowCloseButtonV
   {
     public:
      GuiWindowCloseButtonV();
      void Render();
      void set_model(std::shared_ptr<GuiWindowCloseButton> value)
      {
         model_ = value;
      }

     private:
      std::shared_ptr<GuiWindowCloseButton> model_;
      RenderID rid_close_btn_img_;
   };
}
