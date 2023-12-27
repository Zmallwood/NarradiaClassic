#if 1
#include "scene_mngr_c.h"
#include "scenes/intro/intro_scene_c.h"
#include "scenes/main/main_scene_c.h"
#include "scenes/main_menu/main_menu_scene_c.h"
#include "scenes/map_overview_gen/map_overview_gen_scene_c.h"
#include "core/scene_mngr.h"
#include "iscene_c.h"
#endif

namespace Narradia
{
   SceneMngrC::SceneMngrC()
   {
      scene_controllers_[SceneNames::Intro] = IntroSceneC::get();
      scene_controllers_[SceneNames::MainMenu] = MainMenuSceneC::get();
      scene_controllers_[SceneNames::MapOverviewGen] = MapOverViewGenSceneC::get();
      scene_controllers_[SceneNames::Main] = MainSceneC::get();
   }
   auto SceneMngrC::UpdateGameFlowCurrScene() -> void
   {
      SceneMngr::get()->set_curr_scene_canceled(false);
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }
   auto SceneMngrC::ChangeScene(SceneNames new_scene) -> void
   {
      SceneMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
      SceneMngr::get()->set_curr_scene_canceled(true);
   }
}
