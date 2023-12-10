#pragma once
#include "core/controller/iscene_controller.h"
namespace Narradia {
  /**
   Controller for IntroScene.
  */
  class IntroSceneController : public ISceneController, public Singleton<IntroSceneController> {
   private:
    void OnEnter() override;
    void UpdateGameFlowDerived() override;
  };
}
