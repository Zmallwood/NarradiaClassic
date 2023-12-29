#pragma once

#include "gui-core.h"

namespace Narradia
{
   class StatusPanel : public GuiComponent, public S<StatusPanel>
   {
     public:
      void UpdateGameLogic() override;

      static constexpr RectF kBoundsPanel = {0.0f, 0.0f, 0.2f, 0.18f};
      static constexpr RectF kHpBarBounds = {0.08f, 0.11f, 0.1f, 0.01f};
      static constexpr RectF kStaminaBarBounds = {0.08f, 0.14f, 0.1f, 0.01f};
   };

   class ExperienceBar : public GuiComponent
   {
     public:
      void UpdateGameLogic() override;

      static constexpr float kBarHeight = 0.025f;
   };
}
