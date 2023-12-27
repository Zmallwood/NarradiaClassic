#pragma once

#include "gui-core/m/gui_component.h"

namespace Narradia
{
   class ExperienceBar : public GuiComponent
   {
     public:
      void UpdateGameLogic() override;

      static constexpr float kBarHeight = 0.025f;
   };
}
