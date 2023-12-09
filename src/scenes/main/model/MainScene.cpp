#include "MainScene.h"
#include "main_scene.modules.world_view/model/WorldViewModule.h"
#include "main_scene.modules/model/FPSCounterModule.h"
#include "main_scene.modules/model/KeyboardMovementModule.h"
#include "main_scene.modules/model/MouseRotationModule.h"

namespace Narradia
{
    /**
     * Update game logic.
     */
    void MainScene::UpdateGameLogicDerived()
    {
        WorldViewModule::Get()->UpdateGameLogic();
        MouseRotationModule::Get()->UpdateGameLogic();
        KeyboardMovementModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
