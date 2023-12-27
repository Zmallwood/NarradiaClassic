#if 1
#include "scene_mngr_v.h"
#include "scenes/intro/intro_scene_v.h"
#include "scenes/main/main_scene_v.h"
#include "scenes/main_menu/main_menu_scene_v.h"
#include "scenes/map_overview_gen/map_overview_gen_scene_v.h"
#include "core/scene_mngr.h"
#include "iscene_v.h"
#endif

namespace Narradia
{
   SceneMngrV::SceneMngrV()
   {
      scene_views_[SceneNames::Intro] = IntroSceneV::get();
      scene_views_[SceneNames::MainMenu] = MainMenuSceneV::get();
      scene_views_[SceneNames::MapOverviewGen] = MapOverviewGenSceneV::get();
      scene_views_[SceneNames::Main] = MainSceneV::get();
   }
   auto SceneMngrV::RenderCurrScene() -> void
   {
      if (SceneMngr::get()->curr_scene_canceled())
         return;
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_views_.count(curr_scene) != 0)
         scene_views_.at(curr_scene)->Render();
   }
}
