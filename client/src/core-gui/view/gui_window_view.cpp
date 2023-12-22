#include "gui_window_view.h"
#include "../../core-render-text/view/command/draw_string.h"
#include "../../core-render-text/view/command/new_string.h"
#include "../../core-render/view/command/draw_image.h"
#include "../../core-render/view/command/new_image.h"
namespace Narradia
{
   GuiWindowView::GuiWindowView()
       : gui_window_close_button_view_(std::make_shared<GuiWindowCloseButtonView>()) {
      rid_background_ = NewImage();
      rid_title_bar_ = NewImage();
      rid_title_text_ = NewString();
   }

   void GuiWindowView::Render() {
      auto model = static_pointer_cast<GuiWindow>(gui_component_);
      if (!model->visible())
         return;
      DrawImage(model->background_image_name(), rid_background_, model->Bounds());
      DrawImage("GuiWindowTitleBar", rid_title_bar_, model->AbsTitleBarBounds());
      gui_window_close_button_view_->Render();
      DrawString(
          rid_title_text_, model->title(),
          model->Bounds().GetPosition().Translate(0.005f, 0.01f));
      RenderDerived();
      GuiMovableContainerView::Render();
   }
}
