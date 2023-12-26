#pragma once
#include "../../scenes/intro/c/intro_scene_controller.h"
#include "../../scenes/main/c/main_scene_controller.h"
#include "../../scenes/main_menu/c/main_menu_scene_controller.h"
#include "../../scenes/map_overview_gen/c/map_overview_gen_scene_controller.h"
#include "../m/scene_names.h"
#include "core/m/scene_mngr.h"
#include "iscene_controller.h"
#include <map>
#include <memory>
namespace Narradia
{
   class SceneMngrController : public Singleton<SceneMngrController>
   {
     public:
      SceneMngrController();
      auto UpdateGameFlowCurrScene() -> void;
      auto ChangeScene(SceneNames new_scene) -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneController>> scene_controllers_;
   };
}
