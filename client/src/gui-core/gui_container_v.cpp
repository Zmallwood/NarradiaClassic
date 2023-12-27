#if 1
#include "gui_container_v.h"
#include "gui-core/gui_container.h"
#endif

namespace Narradia
{
   void GuiContainerV::Render()
   {
      for (auto &comp_view : gui_component_views_)
         comp_view->Render();
   }
   void GuiContainerV::AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view)
   {
      auto comp_model = gui_container_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
}
