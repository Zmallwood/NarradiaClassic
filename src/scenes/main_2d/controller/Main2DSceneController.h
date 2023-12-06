#pragma once
#include "../../../core/controller/ISceneController.h"

namespace Narradia {
    /**
     * Controller for MainScene.
     */
    class Main2DSceneController : public ISceneController,
                                  public Singleton<Main2DSceneController> {
      public:
        void OnEnter() override;

      private:
        void UpdateGameFlowDerived() override;
    };
}
