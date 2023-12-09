#pragma once
#include "../model/SceneNames.h"
#include "ISceneView.h"

namespace Narradia
{
    /**
     View for SceneMngr.
    */
    class SceneMngrView : public Singleton<SceneMngrView> {
      public:
        SceneMngrView();
        void RenderCurrScene();

      private:
        std::map<SceneNames, std::shared_ptr<ISceneView>> scene_views_;
    };
}
