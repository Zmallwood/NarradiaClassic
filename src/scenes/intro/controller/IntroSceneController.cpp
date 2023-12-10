#include "IntroSceneController.h"
#include "../../../core.input/model/KeyboardInput.h"
#include "../../../core/controller/SceneMngrController.h"
#include "core.input/model/MouseInput.h"

namespace Narradia {
    /**
     On entering scene.
    */
    void IntroSceneController::OnEnter() {
    }

    /**
     Update game flow between scenes.
    */
    void IntroSceneController::UpdateGameFlowDerived() {
        if (KeyboardInput::Get()->AnyKeyIsPressedPickResult()) {
            SceneMngrController::Get()->ChangeScene(SceneNames::MainMenu);
        }
        MouseInput::Get()->left_button()->AddFiredAction(
            [] { SceneMngrController::Get()->ChangeScene(SceneNames::MainMenu); });
        MouseInput::Get()->right_button()->AddFiredAction(
            [] { SceneMngrController::Get()->ChangeScene(SceneNames::MainMenu); });
    }
}
