#include "main_scene_controller.h"
#include "core/model/text_out_box.h"
#include "main_scene.modules/model/player_spawn_positioning_module.h"
namespace Narradia {
  /**
   On entering scene.
  */
  void MainSceneController::OnEnter() {
    TextOutBox::Get()->Print("Entering Narradia");
    PlayerSpawnPositioningModule::Get()->SpawnAtGoodLocation();
  }

  /**
   Update game flow between scenes.
  */
  void MainSceneController::UpdateGameFlowDerived() {
  }
}
