#pragma once

namespace Narradia
{
   class GuiComponent;

   class SceneGui
   {
     public:
      SceneGui()
          : gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>())
      {
      }
      void UpdateGameLogic();
      void AddGuiComponent(std::shared_ptr<GuiComponent> comp);
      void RemoveGuiComponent(std::shared_ptr<GuiComponent> comp);
      auto gui_components()
      {
         return gui_components_;
      }

     private:
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };
}
