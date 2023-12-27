#if 1
#include "scene_gui_view.h"
#include "gui-core/m/scene_gui.h"
#include "gui_component_view.h"
#endif

namespace Narradia
{
   auto SceneGuiView::Render() -> void
   {
      for (auto gui_component_view : gui_component_views_)
         gui_component_view->Render();
   }

   auto SceneGuiView::AddGuiComponentView(std::shared_ptr<GuiComponentView> comp_view) -> void
   {
      auto comp_model = scene_gui_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
}
