#if 1
#include "scene_gui_v.h"
#include "gui-core/scene_gui.h"
#include "gui_component_v.h"
#endif

namespace Narradia
{
   void SceneGuiV::Render()
   {
      for (auto gui_component_view : gui_component_views_)
         gui_component_view->Render();
   }
   void SceneGuiV::AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view)
   {
      auto comp_model = scene_gui_->gui_components()->at(gui_component_views_.size());
      comp_view->set_gui_component(comp_model);
      gui_component_views_.push_back(comp_view);
   }
}
