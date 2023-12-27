#pragma once

#include "core/scene_names.h"

namespace Narradia
{
   class ISceneC;

   class SceneMngrC : public S<SceneMngrC>
   {
     public:
      SceneMngrC();
      auto UpdateGameFlowCurrScene() -> void;
      auto ChangeScene(SceneNames new_scene) -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneC>> scene_controllers_;
   };
}
