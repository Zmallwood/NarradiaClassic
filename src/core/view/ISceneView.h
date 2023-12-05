#pragma once
#include "core.gui/view/SceneGuiView.h"

namespace Narradia {
    /**
     * View for IScene.
     */
    class ISceneView {
      public:
        ISceneView()
            : scene_gui_view_(std::make_shared<SceneGuiView>()) {
        }

        void Render();

        std::shared_ptr<SceneGuiView> scene_gui_view() {
            return scene_gui_view_;
        }

      protected:
        virtual void RenderDerived() = 0;

        std::shared_ptr<SceneGuiView> scene_gui_view_;
    };
}
