#if 1
#include "gui_window_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#include "gui_window_close_button_v.h"
#include "gui-core/gui_window.h"
#endif

namespace Narradia
{
   GuiWindowV::GuiWindowV()
       : gui_window_close_button_view_(std::make_shared<GuiWindowCloseButtonV>())
   {
      rid_background_ = NewImage();
      rid_title_bar_ = NewImage();
      rid_title_text_ = NewString();
   }
   void GuiWindowV::Render()
   {
      auto model = static_pointer_cast<GuiWindow>(gui_component_);
      if (!model->visible())
         return;
      DrawImage(model->background_image_name(), rid_background_, model->Bounds());
      DrawImage("GuiWindowTitleBar", rid_title_bar_, model->AbsTitleBarBounds());
      gui_window_close_button_view_->Render();
      DrawString(
          rid_title_text_, model->title(), model->Bounds().GetPosition().Translate(0.005f, 0.01f));
      RenderDerived();
      GuiMovableContainerV::Render();
   }
}
