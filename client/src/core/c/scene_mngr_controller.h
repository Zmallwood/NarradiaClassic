#pragma once

#include "core/m/scene_names.h"

namespace Narradia
{
   class ISceneController;

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
