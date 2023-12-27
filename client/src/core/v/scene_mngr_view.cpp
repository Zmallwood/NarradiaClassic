#include "scene_mngr_view.h"
#include "scenes/intro/v/intro_scene_view.h"
#include "scenes/main/v/main_scene_view.h"
#include "scenes/main_menu/v/main_menu_scene_view.h"
#include "scenes/map_overview_gen/v/map_overview_gen_scene_view.h"
#include "core/m/scene_mngr.h"
#include "iscene_view.h"

namespace Narradia
{
   SceneMngrView::SceneMngrView()
   {
      scene_views_[SceneNames::Intro] = IntroSceneView::get();
      scene_views_[SceneNames::MainMenu] = MainMenuSceneView::get();
      scene_views_[SceneNames::MapOverviewGen] = MapOverviewGenSceneView::get();
      scene_views_[SceneNames::Main] = MainSceneView::get();
   }

   auto SceneMngrView::RenderCurrScene() -> void
   {
      if (SceneMngr::get()->curr_scene_canceled())
         return;
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_views_.count(curr_scene) != 0)
         scene_views_.at(curr_scene)->Render();
   }
}
