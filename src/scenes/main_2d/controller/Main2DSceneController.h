#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for MainScene.
     */
    class Main2DSceneController : public ISceneController,
                                public Singleton<Main2DSceneController> {
      private:
        void UpdateGameFlowDerived() override;
    };
}
