#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     * Model for MainScene.
     */
    class MainScene : public IScene {
      private:
        void UpdateGameLogicDerived() override;
    };
}
