#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for IntroScene.
     */
    class IntroSceneView : public ISceneView {
      public:
        IntroSceneView();

      private:
        void RenderDerived() override;

        RenderId rid_box;
        RenderId rid_background;
        RenderId rid_text;
    };
}
