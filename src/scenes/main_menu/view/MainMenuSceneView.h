#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     View for MainMenuScene.
    */
    class MainMenuSceneView : public ISceneView, public Singleton<MainMenuSceneView> {
      public:
        MainMenuSceneView();

      private:
        void RenderDerived() override;

        RenderId rid_background;
        RenderId rid_logo;
    };
}
