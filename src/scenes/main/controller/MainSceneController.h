#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for MainScene.
     */
    class MainSceneController : public ISceneController,
                                public Singleton<MainSceneController> {
      private:
        void UpdateGameFlowDerived() override;
    };
}
