#if 1
#include "gui_button_view.h"
#include "gui-core/m/gui_button.h"
#include "render-text/v/cmd/draw_string.h"
#include "render-text/v/cmd/new_string.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#endif

namespace Narradia
{
   GuiButtonView::GuiButtonView()
   {
      rid_image = NewImage();
      rid_label_text_ = NewString();
   }

   auto GuiButtonView::Render() -> void
   {
      auto model = std::static_pointer_cast<GuiButton>(gui_component_);
      std::string_view used_image_name;
      if (model->hovered())
      {
         used_image_name = model->hovered_img_name();
      }
      else
      {
         used_image_name = model->img_name();
      }
      auto used_bounds = model->bounds();
      //        if (p->parent_container_) {
      //            used_bounds.x +=
      //            p->parent_container_->GetPosition().x;
      //            used_bounds.y +=
      //            p->parent_container_->GetPosition().y;
      //        }
      DrawImage(used_image_name, rid_image, used_bounds);
      DrawString(rid_label_text_, model->text(), used_bounds.GetCenter(), Colors::wheat, true);
   }
}
