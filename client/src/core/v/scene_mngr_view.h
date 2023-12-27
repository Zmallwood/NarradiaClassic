#pragma once

#include "core/m/scene_names.h"

namespace Narradia
{
   class ISceneView;

   class SceneMngrView : public Singleton<SceneMngrView>
   {
     public:
      SceneMngrView();

      auto RenderCurrScene() -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneView>> scene_views_;
   };
}
