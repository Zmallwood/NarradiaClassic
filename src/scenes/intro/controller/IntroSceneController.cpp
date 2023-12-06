#include "IntroSceneController.h"
#include "../../../core.input/model/KeyboardInput.h"
#include "../../../core/controller/SceneMngrController.h"
#include "core.input/model/MouseInput.h"

namespace Narradia {
    void IntroSceneController::OnEnter() {
    }

    /**
     * Update game flow between scenes.
     */
    void IntroSceneController::UpdateGameFlowDerived() {
        if (KeyboardInput::Get()->AnyKeyIsPressedPickResult() ||
            MouseInput::Get()->AnyButtonBeenFiredPickResult()) {
            SceneMngrController::Get()->ChangeScene(SceneNames::MainMenu);
        }
    }
}
