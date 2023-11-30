#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     * Model for IntroScene.
     */
    class IntroScene : public IScene {
      private:
        void UpdateGameLogicDerived() override;
    };
}
