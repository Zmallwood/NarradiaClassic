#include "Main2DSceneController.h"
#include "main_2d_scene.modules/model/PlayerSpawnPositioningModule.h"

namespace Narradia {
    void Main2DSceneController::OnEnter() {
        PlayerSpawnPositioningModule::Get()->SpawnAtGoodLocation();
    }

    /**
     * Update game flow between scenes.
     */
    void Main2DSceneController::UpdateGameFlowDerived() {
    }
}
