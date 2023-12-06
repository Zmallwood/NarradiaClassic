#pragma once

namespace Narradia {
    /**
     * Controller for all IScenes.
     */
    class ISceneController {
      public:
        virtual void OnEnter() = 0;

        void UpdateGameFlow();

      protected:
        virtual void UpdateGameFlowDerived() = 0;
    };
}
