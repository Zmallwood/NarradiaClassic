#pragma once
#include "../../scenes/intro/controller/intro_scene_controller.h"
#include "../../scenes/main/controller/main_scene_controller.h"
#include "../../scenes/main_menu/controller/main_menu_scene_controller.h"
#include "../../scenes/map_overview_gen/controller/map_overview_gen_scene_controller.h"
#include "../model/scene_names.h"
#include "core/model/scene_mngr.h"
#include "iscene_controller.h"
#include <map>
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Controller for SceneMngr.
   ////////////////////////////////////////////////////////////////////////////////
   class SceneMngrController : public Singleton<SceneMngrController> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Initialize scene controllers that will be used.
      ////////////////////////////////////////////////////////////////////////////////
      SceneMngrController();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update game flow between scenes for currently displayed scene.
      ////////////////////////////////////////////////////////////////////////////////
      auto UpdateGameFlowCurrScene() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Change to another scene.
      /// @param[in] new_scene Scene to change to.
      ////////////////////////////////////////////////////////////////////////////////
      auto ChangeScene(SceneNames new_scene) -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneController>> scene_controllers_;
   };
}
