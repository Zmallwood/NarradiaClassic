#include "MainSceneController.h"
#include "core/model/TextOutBox.h"
#include "main_scene.modules/model/PlayerSpawnPositioningModule.h"

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
