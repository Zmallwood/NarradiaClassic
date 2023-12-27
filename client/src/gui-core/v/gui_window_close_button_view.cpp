#if 1
#include "gui_window_close_button_view.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "gui-core/m/gui_window_close_button.h"
#endif

namespace Narradia
{
   GuiWindowCloseButtonView::GuiWindowCloseButtonView()
   {
      rid_close_btn_img_ = NewImage();
   }

   void GuiWindowCloseButtonView::Render()
   {
      if (model_->hovered())
         DrawImage("GuiWindowCloseButtonHovered", rid_close_btn_img_, model_->Bounds());
      else
         DrawImage("GuiWindowCloseButton", rid_close_btn_img_, model_->Bounds());
   }
}
