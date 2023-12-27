#pragma once

#include "gui-core/gui_component.h"

namespace Narradia
{
   class GuiComponentV
   {
     public:
      virtual void Render() = 0;
      auto gui_component()
      {
         return gui_component_;
      }
      void set_gui_component(std::shared_ptr<GuiComponent> value)
      {
         gui_component_ = value;
      }

     protected:
      std::shared_ptr<GuiComponent> gui_component_;
   };
}
