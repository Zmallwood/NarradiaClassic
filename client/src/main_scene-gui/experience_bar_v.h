#pragma once

#include "gui-core_v.h"

namespace Narradia
{
   class ExperienceBarV : public GuiComponentV
   {
     public:
      ExperienceBarV();
      void Render() override;

     private:
      RenderID rid_unfilled_area_;
      RenderID rid_filled_area_;
      RenderID rid_text_;
   };
}
