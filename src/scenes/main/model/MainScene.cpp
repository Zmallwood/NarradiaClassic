#include "MainScene.h"
#include "main_scene.modules/model/FPSCounterModule.h"

namespace Narradia {
    /**
     * Update game logic.
     */
    void MainScene::UpdateGameLogicDerived() {
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
