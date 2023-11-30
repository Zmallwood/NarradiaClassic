#include "SceneMngr.h"
#include "../../scenes/intro/model/IntroScene.h"
#include "../../scenes/main/model/MainScene.h"
#include "../../scenes/main_menu/model/MainMenuScene.h"

namespace Narradia {
    /**
     * Initialize scenes that will be used.
     */
    SceneMngr::SceneMngr() {
        scenes_.insert({SceneNames::Intro, std::make_shared<IntroScene>()});
        scenes_.insert(
            {SceneNames::MainMenu, std::make_shared<MainMenuScene>()});
        scenes_.insert({SceneNames::Main, std::make_shared<MainScene>()});

        curr_scene_ = SceneNames::Intro;
    }

    /**
     * Update game logic for currently displayed scene.
     */
    void SceneMngr::UpdateGameLogicCurrScene() {

        if (scenes_.count(curr_scene_) != 0)
            scenes_.at(curr_scene_)->UpdateGameLogic();
    }
}
