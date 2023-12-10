#include "scene_mngr.h"
#include "../../scenes/intro/model/intro_scene.h"
#include "../../scenes/main/model/main_scene.h"
#include "../../scenes/main_menu/model/main_menu_scene.h"

namespace Narradia {
  /**
   Initialize scenes that will be used.
  */
  SceneMngr::SceneMngr() {
    scenes_.insert({SceneNames::Intro, IntroScene::Get()});
    scenes_.insert({SceneNames::MainMenu, MainMenuScene::Get()});
    scenes_.insert({SceneNames::Main, MainScene::Get()});
    curr_scene_ = SceneNames::Intro;
  }

  /**
   Update game logic for currently displayed scene.
  */
  void SceneMngr::UpdateGameLogicCurrScene() {
    if (scenes_.count(curr_scene_) != 0)
      scenes_.at(curr_scene_)->UpdateGameLogic();
  }
}
