#pragma once
#include "core.gui/model/GuiComponent.h"

namespace Narradia {
    class GuiComponentView {
      public:
        virtual void Render() = 0;

        std::shared_ptr<GuiComponent> gui_component() {
            return gui_component_;
        }

        void set_gui_component(std::shared_ptr<GuiComponent> value) {
            gui_component_ = value;
        }

      protected:
        std::shared_ptr<GuiComponent> gui_component_;
    };
}
