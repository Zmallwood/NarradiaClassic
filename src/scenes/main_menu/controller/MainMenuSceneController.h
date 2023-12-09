#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     Controller for MainMenuScene.
    */
    class MainMenuSceneController : public ISceneController,
                                    public Singleton<MainMenuSceneController> {
      public:
        void OnEnter() override;

      private:
        void UpdateGameFlowDerived() override;
    };
}
