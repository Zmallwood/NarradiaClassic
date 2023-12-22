#include "gui_window_close_button_view.h"
#include "../../core-render/view/command/draw_image.h"
#include "../../core-render/view/command/new_image.h"
namespace Narradia
{
   GuiWindowCloseButtonView::GuiWindowCloseButtonView() {
      rid_close_btn_img_ = NewImage();
   }

   void GuiWindowCloseButtonView::Render() {
      if (model_->hovered())
         DrawImage("GuiWindowCloseButtonHovered", rid_close_btn_img_, model_->Bounds());
      else
         DrawImage("GuiWindowCloseButton", rid_close_btn_img_, model_->Bounds());
   }
}
