#include "scene_gui.h"
namespace Narradia
{
   auto SceneGui::UpdateGameLogic() -> void
   {
      for (auto comp : *gui_components_)
         comp->UpdateGameLogic();
   }

   auto SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> comp) -> void
   {
      gui_components_->push_back(comp);
   }

   auto SceneGui::RemoveGuiComponent(std::shared_ptr<GuiComponent> comp) -> void
   {
      auto i = 0;
      for (auto &entry : *gui_components_)
      {
         if (entry.get() == comp.get())
         {
            gui_components_->erase(gui_components_->begin() + i);
            break;
         }
         i++;
      }
   }
}
