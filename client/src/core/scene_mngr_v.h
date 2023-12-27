#pragma once

#include "core/scene_names.h"

namespace Narradia
{
   class ISceneV;

   class SceneMngrV : public S<SceneMngrV>
   {
     public:
      SceneMngrV();
      void RenderCurrScene();

     private:
      std::map<SceneNames, std::shared_ptr<ISceneV>> scene_views_;
   };
}
