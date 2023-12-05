#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for MainMenuScene.
     */
    class MainMenuSceneView : public ISceneView {
      public:
        MainMenuSceneView();

      private:
        void RenderDerived() override;

        RenderId rid_box;
        RenderId rid_background;
    };
}
