#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for MainMenuScene.
     */
    class MainMenuSceneController : public ISceneController,
                                    public Singleton<MainMenuSceneController> {
      private:
        void UpdateGameFlowDerived() override;
    };
}
