#pragma once

#include "gui-core.h"

namespace Narradia
{
   class ExperienceBar : public GuiComponent
   {
     public:
      void UpdateGameLogic() override;

      static constexpr float kBarHeight = 0.025f;
   };
}
