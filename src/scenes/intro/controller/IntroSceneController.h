#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for IntroScene.
     */
    class IntroSceneController : public ISceneController {
      private:
        void UpdateGameFlowDerived() override;
    };
}
