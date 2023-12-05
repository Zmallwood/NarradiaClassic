#include "SceneMngrController.h"
#include "../../scenes/intro/controller/IntroSceneController.h"
#include "../../scenes/main/controller/MainSceneController.h"
#include "../../scenes/main_menu/controller/MainMenuSceneController.h"
#include "../model/SceneMngr.h"

namespace Narradia {
    /**
     * Initialize scene controllers that will be used.
     */
    SceneMngrController::SceneMngrController() {
        scene_controllers_.insert(
            {SceneNames::Intro, std::make_shared<IntroSceneController>()});
        scene_controllers_.insert(
            {SceneNames::MainMenu,
             std::make_shared<MainMenuSceneController>()});
        scene_controllers_.insert(
            {SceneNames::Main, std::make_shared<MainSceneController>()});
    }

    /**
     * Update game flow between scenes for currently displayed scene.
     */
    void SceneMngrController::UpdateGameFlowCurrScene() {
        auto curr_scene = SceneMngr::Get()->curr_scene();

        if (scene_controllers_.count(curr_scene) != 0)
            scene_controllers_.at(curr_scene)->UpdateGameFlow();
    }

    /**
     * Change to another scene.
     */
    void SceneMngrController::ChangeScene(SceneNames new_scene) {
        SceneMngr::Get()->set_curr_scene(new_scene);
    }
//    string SceneMngrController::LakSho() {
//        return "Laksh0!!!";
//    }
}
