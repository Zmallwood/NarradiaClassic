#include "main_scene_controller.h"
#include "core/model/console.h"
#include "main_scene-modules/model/player_spawn_positioning_module.h"
namespace Narradia
{
    /**
     On entering scene.
    */
    void MainSceneController::OnEnter() {
        Console::get()->Print("Entering Narradia");
        PlayerSpawnPositioningModule::get()->SpawnAtGoodLocation();
    }

    /**
     Update game flow between scenes.
    */
    void MainSceneController::UpdateGameFlowDerived() {
    }
}
