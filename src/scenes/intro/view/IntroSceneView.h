#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia {
    /**
     View for IntroScene.
    */
    class IntroSceneView : public ISceneView, public Singleton<IntroSceneView> {
      public:
        IntroSceneView();

      private:
        void RenderDerived() override;

        RenderID rid_background;
        RenderID rid_logo;
        RenderID rid_text;
    };
}
