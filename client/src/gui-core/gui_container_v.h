#pragma once

#include "gui_component_v.h"

namespace Narradia
{
   class GuiContainer;

   class GuiContainerV : public GuiComponentV
   {
     protected:
      void Render() override;
      void AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view);
      void set_gui_container(std::shared_ptr<GuiContainer> value)
      {
         gui_container_ = value;
      }

     private:
      std::shared_ptr<GuiContainer> gui_container_;
      std::vector<std::shared_ptr<GuiComponentV>> gui_component_views_;
   };
}
