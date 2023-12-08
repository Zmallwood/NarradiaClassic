#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {

    /**
     * View for MainScene.
     */
    class MainSceneView : public ISceneView, public Singleton<MainSceneView> {
      public:
        MainSceneView();

      private:
        void RenderDerived() override;
    };
}
