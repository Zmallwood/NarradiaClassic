#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia {
    /**
     * Model for Main2DScene.
     */
    class Main2DScene : public IScene, public Singleton<Main2DScene> {
      public:
        Main2DScene();

      private:
        void UpdateGameLogicDerived() override;
    };
}
