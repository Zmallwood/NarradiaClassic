#if 1
#include "scene_mngr_controller.h"
#include "scenes/intro/c/intro_scene_controller.h"
#include "scenes/main/c/main_scene_controller.h"
#include "scenes/main_menu/c/main_menu_scene_controller.h"
#include "scenes/map_overview_gen/c/map_overview_gen_scene_controller.h"
#include "core/m/scene_mngr.h"
#include "iscene_controller.h"
#endif

namespace Narradia
{
   SceneMngrController::SceneMngrController()
   {
      scene_controllers_[SceneNames::Intro] = IntroSceneController::get();
      scene_controllers_[SceneNames::MainMenu] = MainMenuSceneController::get();
      scene_controllers_[SceneNames::MapOverviewGen] = MapOverViewGenSceneController::get();
      scene_controllers_[SceneNames::Main] = MainSceneController::get();
   }

   auto SceneMngrController::UpdateGameFlowCurrScene() -> void
   {
      SceneMngr::get()->set_curr_scene_canceled(false);
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }

   auto SceneMngrController::ChangeScene(SceneNames new_scene) -> void
   {
      SceneMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
      SceneMngr::get()->set_curr_scene_canceled(true);
   }
}
