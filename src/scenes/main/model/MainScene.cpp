#include "MainScene.h"
#include "main_scene.modules/model/FPSCounterModule.h"
#include "main_scene.modules/model/KeyboardMovementModule.h"

namespace Narradia {
    /**
     * Update game logic.
     */
    void MainScene::UpdateGameLogicDerived() {
        KeyboardMovementModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
