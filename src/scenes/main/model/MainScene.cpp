#include "MainScene.h"
#include "main_scene.modules/model/KeyboardMovementModule.h"
#include "main_scene.modules/model/TileHoveringModule.h"

namespace Narradia {
    /**
     * Update game logic.
     */
    void MainScene::UpdateGameLogicDerived() {
        KeyboardMovementModule::Get()->UpdateGameLogic();
        TileHoveringModule::Get()->UpdateGameLogic();
    }
}
