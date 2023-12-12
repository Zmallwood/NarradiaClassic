#include "scene_mngr_controller.h"
#include "core/model/scene_mngr.h"
#include "scenes/intro/controller/intro_scene_controller.h"
#include "scenes/main/controller/main_scene_controller.h"
#include "scenes/main_menu/controller/main_menu_scene_controller.h"
namespace Narradia
{
    /**
     Initialize scene controllers that will be used.
    */
    SceneMngrController::SceneMngrController() {
        scene_controllers_.insert({SceneNames::Intro, IntroSceneController::Get()});
        scene_controllers_.insert({SceneNames::MainMenu, MainMenuSceneController::Get()});
        scene_controllers_.insert({SceneNames::Main, MainSceneController::Get()});
    }

    /**
     Update game flow between scenes for currently displayed
     scene.
    */
    void SceneMngrController::UpdateGameFlowCurrScene() {
        auto curr_scene = SceneMngr::Get()->curr_scene();
        if (scene_controllers_.count(curr_scene) != 0)
            scene_controllers_.at(curr_scene)->UpdateGameFlow();
    }

    /**
     Change to another scene.
    */
    void SceneMngrController::ChangeScene(SceneNames new_scene) {
        SceneMngr::Get()->set_curr_scene(new_scene);
        scene_controllers_.at(new_scene)->OnEnter();
    }
}
