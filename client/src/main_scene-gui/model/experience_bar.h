#pragma once
#include "core-gui/model/gui_component.h"
namespace Narradia
{
    class ExperienceBar : public GuiComponent {
      public:
        void UpdateGameLogic() override;

        static constexpr float kBarHeight = 0.025f;
    };
}
