#include "intro_scene_controller.h"
#include "core.input/model/keyboard_input.h"
#include "core.input/model/mouse_input.h"
#include "core/controller/scene_mngr_controller.h"
namespace Narradia
{
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
