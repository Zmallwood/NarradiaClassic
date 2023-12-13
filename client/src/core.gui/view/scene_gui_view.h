#pragma once
#include "../model/scene_gui.h"
#include "gui_component_view.h"
#include <memory>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief View component of SceneGui.
   ////////////////////////////////////////////////////////////////////////////////
   class SceneGuiView {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwards the render request to all contains gui components views.
      ////////////////////////////////////////////////////////////////////////////////
      auto Render() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Adds a new gui component view to the internal data structure, also connects it to
      /// the corresponding model in the scene gui.
      ///
      /// @param[in] comp_view Component view to be added.
      ////////////////////////////////////////////////////////////////////////////////
      auto AddGuiComponentView(std::shared_ptr<GuiComponentView> comp_view) -> void;

      void set_scene_gui(std::shared_ptr<SceneGui> value) {
         scene_gui_ = value;
      }

     private:
      std::shared_ptr<SceneGui> scene_gui_;
      std::vector<std::shared_ptr<GuiComponentView>> gui_component_views_;
   };
}
