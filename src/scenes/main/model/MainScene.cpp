#include "MainScene.h"
#include "main_scene.modules.world_view/model/WorldViewModule.h"
#include "main_scene.modules/model/FPSCounterModule.h"
#include "main_scene.modules/model/KeyboardMovementModule.h"
#include "main_scene.modules/model/MouseRotationModule.h"
#include "main_scene.modules/model/MobMovementModule.h"

namespace Narradia {
    /**
     Update game logic.
    */
    void MainScene::UpdateGameLogicDerived() {
        MobMovementModule::Get()->UpdateGameLogic();
        KeyboardMovementModule::Get()->UpdateGameLogic();
        WorldViewModule::Get()->UpdateGameLogic();
        MouseRotationModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
