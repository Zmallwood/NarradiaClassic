#pragma once
#include "../../../core/view/ISceneView.h"

namespace Narradia
{
    /**
     View for IntroScene.
    */
    class IntroSceneView : public ISceneView, public Singleton<IntroSceneView> {
      public:
        IntroSceneView();

      private:
        void RenderDerived() override;

        RenderId rid_background;
        RenderId rid_logo;
        RenderId rid_text;
    };
}
