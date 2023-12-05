#pragma once
#include "GuiComponent.h"

namespace Narradia {
    class SceneGui {
      public:
        void UpdateGameLogic();

        void AddGuiComponent(std::shared_ptr<GuiComponent> component);

        std::vector<std::shared_ptr<GuiComponent>> &gui_components() {
            return gui_components_;
        }

      private:
        std::vector<std::shared_ptr<GuiComponent>> gui_components_;
    };
}
