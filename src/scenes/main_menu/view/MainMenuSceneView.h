#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for MainMenuScene.
     */
    class MainMenuSceneView : public ISceneView {
      private:
        void RenderDerived() override;
    };
}
