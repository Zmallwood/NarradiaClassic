#pragma once
#include "../../../core/m/iscene.h"
namespace Narradia
{
    /**
     Model for MainScene.
    */
    class MainScene : public IScene, public Singleton<MainScene> {
      public:
        MainScene();
      private:
        void UpdateGameLogicDerived() override;
        void Finalize() override {}
    };
}
