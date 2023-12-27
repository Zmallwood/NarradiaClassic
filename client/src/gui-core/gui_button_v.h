#pragma once

#include "gui_component_v.h"

namespace Narradia
{
   class GuiButtonV : public GuiComponentV
   {
     public:
      GuiButtonV();
      void Render() override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };
}
