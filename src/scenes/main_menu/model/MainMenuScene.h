#pragma once
#include "../../../core/model/IScene.h"

namespace Narradia
{
    /**
     * Model for MainMenuScene.
     */
    class MainMenuScene : public IScene, public Singleton<MainMenuScene> {
      public:
        MainMenuScene();

      private:
        void UpdateGameLogicDerived() override;
    };
}
