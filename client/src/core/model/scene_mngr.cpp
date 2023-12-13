#include "scene_mngr.h"
namespace Narradia
{
   SceneMngr::SceneMngr() {
      scenes_[SceneNames::Intro] = IntroScene::get();
      scenes_[SceneNames::MainMenu] = MainMenuScene::get();
      scenes_[SceneNames::Main] = MainScene::get();
      curr_scene_ = SceneNames::Intro;
   }

   void SceneMngr::UpdateGameLogicCurrScene() {
      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->UpdateGameLogic();
   }
}
