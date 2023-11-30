#pragma once

namespace Narradia {
    /**
     * Controller for all IScenes.
     */
    class ISceneController {
      public:
        void UpdateGameFlow();

      protected:
        virtual void UpdateGameFlowDerived() = 0;
    };
}
