#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     * Model for MainMenuScene.
     */
    class MainMenuScene : public IScene {
      private:
        void UpdateGameLogicDerived() override;
    };
}
