#if 1
#include "scene_gui.h"
#include "gui_component.h"
#endif

namespace Narradia
{
   void SceneGui::UpdateGameLogic()
   {
      for (auto comp : *gui_components_)
         comp->UpdateGameLogic();
   }
   void SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> comp)
   {
      gui_components_->push_back(comp);
   }
   void SceneGui::RemoveGuiComponent(std::shared_ptr<GuiComponent> comp)
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
