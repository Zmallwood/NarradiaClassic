#include "MainScene.h"
#include "main_scene.modules/model/KeyboardMovementModule.h"
#include "main_scene.modules/model/MouseMovementModule.h"
#include "main_scene.modules/model/TileHoveringModule.h"
#include "main_scene.modules/model/FPSCounterModule.h"

namespace Narradia {
    /**
     * Update game logic.
     */
    void MainScene::UpdateGameLogicDerived() {
        KeyboardMovementModule::Get()->UpdateGameLogic();
        MouseMovementModule::Get()->UpdateGameLogic();
        TileHoveringModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
