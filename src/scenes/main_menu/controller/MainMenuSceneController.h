#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for MainMenuScene.
     */
    class MainMenuSceneController : public ISceneController {
      private:
        void UpdateGameFlowDerived() override;
    };
}
