#pragma once
#include "core/controller/iscene_controller.h"
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
