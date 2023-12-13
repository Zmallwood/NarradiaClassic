#include "scene_gui.h"
namespace Narradia
{
   auto SceneGui::UpdateGameLogic() -> void {
      for (auto comp : *gui_components_)
         comp->UpdateGameLogic();
   }

   auto SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> comp) -> void {
      gui_components_->push_back(comp);
   }
}
