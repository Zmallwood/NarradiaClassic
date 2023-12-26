#include "main_scene_controller.h"
#include "core/m/console.h"
#include "main_scene-modules/m/player_spawn_positioning_module.h"
namespace Narradia
{
   void MainSceneController::OnEnter()
   {
      Console::get()->Print("Entering Narradia");
      PlayerSpawnPositioningModule::get()->SpawnAtGoodLocation();
   }

   void MainSceneController::UpdateGameFlowDerived()
   {
   }
}
