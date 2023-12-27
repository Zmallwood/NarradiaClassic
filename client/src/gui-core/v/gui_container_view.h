#pragma once

#include "gui_component_view.h"

namespace Narradia
{
   class GuiContainer;

   class GuiContainerView : public GuiComponentView
   {
     protected:
      void Render() override;
      void AddGuiComponentView(std::shared_ptr<GuiComponentView> comp_view);

      void set_gui_container(std::shared_ptr<GuiContainer> value)
      {
         gui_container_ = value;
      }

     private:
      std::shared_ptr<GuiContainer> gui_container_;
      std::vector<std::shared_ptr<GuiComponentView>> gui_component_views_;
   };
}
