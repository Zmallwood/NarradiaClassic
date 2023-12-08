#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     * View for Main2DScene.
     */
    class Main2DSceneView : public ISceneView, public Singleton<Main2DSceneView> {
      public:
        Main2DSceneView();

      private:
        void RenderDerived() override;
    };
}
