#pragma once

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
