#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for MainScene.
     */
    class MainSceneView : public ISceneView {
      private:
        void RenderDerived() override;
    };
}
