#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {

    /**
     * Controller for IntroScene.
     */
    class IntroSceneController : public ISceneController, public Singleton<IntroSceneController> {
      private:
        void OnEnter() override;
        void UpdateGameFlowDerived() override;
    };
}
