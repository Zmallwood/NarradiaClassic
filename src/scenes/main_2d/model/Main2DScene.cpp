#include "Main2DScene.h"
#include "main_2d_scene.modules/model/FPSCounterModule.h"
#include "main_2d_scene.modules/model/KeyboardMovementModule.h"
#include "main_2d_scene.modules/model/MobMovementModule.h"
#include "main_2d_scene.modules/model/MouseMovementModule.h"
#include "main_2d_scene.modules/model/TileHoveringModule.h"

namespace Narradia {
    /**
     * Update game logic.
     */
    void Main2DScene::UpdateGameLogicDerived() {
        KeyboardMovementModule::Get()->UpdateGameLogic();
        MouseMovementModule::Get()->UpdateGameLogic();
        TileHoveringModule::Get()->UpdateGameLogic();
        MobMovementModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
