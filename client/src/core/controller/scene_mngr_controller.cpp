#include "scene_mngr_controller.h"
namespace Narradia
{
   SceneMngrController::SceneMngrController() {
      scene_controllers_[SceneNames::Intro] = IntroSceneController::get();
      scene_controllers_[SceneNames::MainMenu] = MainMenuSceneController::get();
      scene_controllers_[SceneNames::Main] = MainSceneController::get();
   }

   auto SceneMngrController::UpdateGameFlowCurrScene() -> void {
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_controllers_.count(curr_scene) != 0)
         scene_controllers_.at(curr_scene)->UpdateGameFlow();
   }

   auto SceneMngrController::ChangeScene(SceneNames new_scene) -> void {
      SceneMngr::get()->set_curr_scene(new_scene);
      scene_controllers_.at(new_scene)->OnEnter();
   }
}
