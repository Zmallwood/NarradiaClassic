#pragma once
#include "../../../core/model/iscene.h"

namespace Narradia {
  /**
   Model for MainScene.
  */
  class MainScene : public IScene, public Singleton<MainScene> {
   private:
    void UpdateGameLogicDerived() override;
  };
}