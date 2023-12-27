#if 1
#include "scene_mngr.h"
#include "iscene.h"
#include "scenes/intro/intro_scene.h"
#include "scenes/main/main_scene.h"
#include "scenes/main_menu/main_menu_scene.h"
#include "scenes/map_overview_gen/map_overview_gen_scene.h"
#endif

namespace Narradia
{
   SceneMngr::SceneMngr()
   {
      scenes_[SceneNames::Intro] = IntroScene::get();
      scenes_[SceneNames::MainMenu] = MainMenuScene::get();
      scenes_[SceneNames::MapOverviewGen] = MapOverviewGenScene::get();
      scenes_[SceneNames::Main] = MainScene::get();
      curr_scene_ = SceneNames::Intro;
   }
   void SceneMngr::UpdateGameLogicCurrScene()
   {
      if (curr_scene_canceled_)
         return;
      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->UpdateGameLogic();
   }
   void SceneMngr::FinalizeCurrScene()
   {
      if (curr_scene_canceled_)
         return;
      if (scenes_.count(curr_scene_) != 0)
         scenes_.at(curr_scene_)->Finalize();
   }
}
