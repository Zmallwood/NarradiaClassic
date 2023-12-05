#pragma once
#include "core.gui/model/GuiComponent.h"

namespace Narradia {
    class GuiComponentView {
      public:
        virtual void Render() = 0;

        std::shared_ptr<GuiComponent> gui_component() {
            return gui_component_;
        }

      private:
        std::shared_ptr<GuiComponent> gui_component_;
    };
}
