#pragma once
#include "gui_component.h"
#include <memory>
#include <vector>

namespace Narradia {
  /**
   Model component for SceneGui, of which every Scene has
   an inherited member instance of.
  */
  class SceneGui {
   public:
    void UpdateGameLogic();
    void AddGuiComponent(std::shared_ptr<GuiComponent> component);

    auto &gui_components() {
      return gui_components_;
    }

   private:
    std::vector<std::shared_ptr<GuiComponent>> gui_components_;
  };
}
