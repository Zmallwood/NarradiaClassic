#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     Model for IntroScene.
    */
    class IntroScene : public IScene, public Singleton<IntroScene> {
      private:
        void UpdateGameLogicDerived() override;
    };
}
