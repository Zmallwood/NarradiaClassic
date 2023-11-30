#pragma once

namespace Narradia {
    /**
     * View for IScene.
     */
    class ISceneView {
      public:
        void Render();

      protected:
        virtual void RenderDerived() = 0;
    };
}
