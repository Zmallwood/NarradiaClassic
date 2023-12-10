#pragma once
#include "core/model/iscene.h"
namespace Narradia {
  /**
   Model for IntroScene.
  */
  class IntroScene : public IScene, public Singleton<IntroScene> {
   private:
    void UpdateGameLogicDerived() override;
  };
}
