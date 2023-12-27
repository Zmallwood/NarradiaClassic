#if 1
#include "gui_window_close_button_v.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#include "gui-core/gui_window_close_button.h"
#endif

namespace Narradia
{
   GuiWindowCloseButtonV::GuiWindowCloseButtonV()
   {
      rid_close_btn_img_ = NewImage();
   }
   void GuiWindowCloseButtonV::Render()
   {
      if (model_->hovered())
         DrawImage("GuiWindowCloseButtonHovered", rid_close_btn_img_, model_->Bounds());
      else
         DrawImage("GuiWindowCloseButton", rid_close_btn_img_, model_->Bounds());
   }
}
