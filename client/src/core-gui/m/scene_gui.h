#pragma once
#include "gui_component.h"
#include <memory>
#include <vector>
namespace Narradia
{
   class SceneGui
   {
     public:
      SceneGui()
          : gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>())
      {
      }

      auto UpdateGameLogic() -> void;

      auto AddGuiComponent(std::shared_ptr<GuiComponent> comp) -> void;

      auto RemoveGuiComponent(std::shared_ptr<GuiComponent> comp) -> void;

      auto gui_components()
      {
         return gui_components_;
      }

     private:
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };
}
