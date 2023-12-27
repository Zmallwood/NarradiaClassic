#pragma once

namespace Narradia
{
   class GuiComponentView;
   class SceneGui;

   class SceneGuiView
   {
     public:
      auto Render() -> void;

      auto AddGuiComponentView(std::shared_ptr<GuiComponentView> comp_view) -> void;

      void set_scene_gui(std::shared_ptr<SceneGui> value)
      {
         scene_gui_ = value;
      }

     private:
      std::shared_ptr<SceneGui> scene_gui_;
      std::vector<std::shared_ptr<GuiComponentView>> gui_component_views_;
   };
}
