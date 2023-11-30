#include "MainMenuSceneController.h"
#include "../../../core.input/model/KeyboardInput.h"
#include "../../../core/controller/SceneMngrController.h"

namespace Narradia {
    /**
     * Update game flow between scenes.
     */
    void MainMenuSceneController::UpdateGameFlowDerived() {
        if (KeyboardInput::Get()->AnyKeyIsPressedPickResult()) {
            SceneMngrController::Get()->ChangeScene(SceneNames::Main);
        }
    }
}
