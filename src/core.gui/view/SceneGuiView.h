#pragma once
#include "GuiComponentView.h"
#include "core.gui/model/SceneGui.h"
#include <memory>

namespace Narradia {
    /**
     View component of SceneGui.
    */
    class SceneGuiView {
      public:
        void Render();
        void AddGuiComponentView(std::shared_ptr<GuiComponentView> gui_component_view);

        void set_scene_gui(std::shared_ptr<SceneGui> value) { scene_gui_ = value; }

      private:
        std::shared_ptr<SceneGui> scene_gui_;
        std::vector<std::shared_ptr<GuiComponentView>> gui_component_views_;
    };
}
