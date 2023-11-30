#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for IntroScene.
     */
    class IntroSceneView : public ISceneView {
      private:
        void RenderDerived() override;
    };
}
