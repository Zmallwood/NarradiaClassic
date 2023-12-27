#pragma once

#include "gui-core/m/gui_button.h"
#include "render-text/v/cmd/draw_string.h"
#include "render-text/v/cmd/new_string.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "gui_component_view.h"

namespace Narradia
{
   class GuiButtonView : public GuiComponentView
   {
     public:
      GuiButtonView();

      auto Render() -> void override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };
}
