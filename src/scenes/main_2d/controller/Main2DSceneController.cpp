#include "Main2DSceneController.h"
#include "main_2d_scene.modules/model/PlayerSpawnPositioningModule.h"
#include "core/model/TextOutBox.h"

namespace Narradia {
    /**
     * On entering scene.
     */
    void Main2DSceneController::OnEnter() {
        PlayerSpawnPositioningModule::Get()->SpawnAtGoodLocation();
        TextOutBox::Get()->Print("Entering Narradia");
    }

    /**
     * Update game flow between scenes.
     */
    void Main2DSceneController::UpdateGameFlowDerived() {
    }
}
