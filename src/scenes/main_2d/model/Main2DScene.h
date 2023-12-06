#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     * Model for MainScene.
     */
    class Main2DScene : public IScene, public Singleton<Main2DScene> {
      private:
        void UpdateGameLogicDerived() override;
    };
}
