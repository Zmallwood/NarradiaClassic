#include "intro_scene_controller.h"
#include "core.input/model/kb_input.h"
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
        if (KbInput::get()->AnyKeyIsPressedPickResult()) {
            SceneMngrController::get()->ChangeScene(SceneNames::MainMenu);
        }
        MouseInput::get()->left_btn()->AddFiredAction(
            [] { SceneMngrController::get()->ChangeScene(SceneNames::MainMenu); });
        MouseInput::get()->right_btn()->AddFiredAction(
            [] { SceneMngrController::get()->ChangeScene(SceneNames::MainMenu); });
    }
}
