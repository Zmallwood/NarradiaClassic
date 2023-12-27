#pragma once

namespace Narradia
{
   class GuiComponentV;
   class SceneGui;

   class SceneGuiV
   {
     public:
      void Render();
      void AddGuiComponentView(std::shared_ptr<GuiComponentV> comp_view);
      void set_scene_gui(std::shared_ptr<SceneGui> value)
      {
         scene_gui_ = value;
      }

     private:
      std::shared_ptr<SceneGui> scene_gui_;
      std::vector<std::shared_ptr<GuiComponentV>> gui_component_views_;
   };
}
