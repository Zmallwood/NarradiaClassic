#pragma once
#include "core.gui/model/gui_component.h"
#include <memory>
namespace Narradia
{
    /**
     View component of the GuiComponent.
    */
    class GuiComponentView {
      public:
        virtual void Render() = 0;

        auto gui_component() {
            return gui_component_;
        }
        void set_gui_component(std::shared_ptr<GuiComponent> value) {
            gui_component_ = value;
        }
      protected:
        std::shared_ptr<GuiComponent> gui_component_;
    };
}
