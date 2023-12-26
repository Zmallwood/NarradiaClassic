#pragma once
#include "scenes/intro/v/intro_scene_view.h"
#include "scenes/main/v/main_scene_view.h"
#include "scenes/main_menu/v/main_menu_scene_view.h"
#include "scenes/map_overview_gen/v/map_overview_gen_scene_view.h"
#include "../m/scene_mngr.h"
#include "../m/scene_names.h"
#include "iscene_view.h"
namespace Narradia
{
   class SceneMngrView : public Singleton<SceneMngrView>
   {
     public:
      SceneMngrView();

      auto RenderCurrScene() -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneView>> scene_views_;
   };
}
