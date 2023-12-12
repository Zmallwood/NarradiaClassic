#pragma once
#include "core/controller/iscene_controller.h"
namespace Narradia
{
    /**
     Controller for MainScene.
    */
    class MainSceneController : public ISceneController, public Singleton<MainSceneController> {
      public:
        void OnEnter() override;
      private:
        void UpdateGameFlowDerived() override;
    };
}
