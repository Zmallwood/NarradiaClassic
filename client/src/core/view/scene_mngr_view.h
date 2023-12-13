#pragma once
#include "core/model/scene_names.h"
#include "iscene_view.h"
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
