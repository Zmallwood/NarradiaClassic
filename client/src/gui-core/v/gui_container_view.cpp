#include "gui_container_view.h"
#include "gui-core/m/gui_container.h"

namespace Narradia
{
   void GuiContainerView::Render()
   {
      for (auto &comp_view : gui_component_views_)
         comp_view->Render();
   }

   void GuiContainerView::AddGuiComponentView(std::shared_ptr<GuiComponentView> comp_view)
   {
      auto comp_model = gui_container_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
}
