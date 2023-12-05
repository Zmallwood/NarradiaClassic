#pragma once
#include "core.gui/model/SceneGui.h"

namespace Narradia {
    class SceneGuiView {
      public:
        void Render();

        void set_scene_gui(std::shared_ptr<SceneGui> value) {
            scene_gui_ = value;
        }

      private:
        std::shared_ptr<SceneGui> scene_gui_;
    };
}
