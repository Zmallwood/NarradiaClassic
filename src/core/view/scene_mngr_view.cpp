#include "scene_mngr_view.h"
#include "scenes/intro/view/intro_scene_view.h"
#include "scenes/main/view/main_scene_view.h"
#include "scenes/main_menu/view/main_menu_scene_view.h"
#include "core/model/scene_mngr.h"
namespace Narradia {
  /**
   Initialize scene views that will be used.
  */
  SceneMngrView::SceneMngrView() {
    scene_views_.insert({SceneNames::Intro, IntroSceneView::Get()});
    scene_views_.insert({SceneNames::MainMenu, MainMenuSceneView::Get()});
    scene_views_.insert({SceneNames::Main, MainSceneView::Get()});
  }

  /**
   Render currently displayed scene.
  */
  void SceneMngrView::RenderCurrScene() {
    auto curr_scene = SceneMngr::Get()->curr_scene();
    if (scene_views_.count(curr_scene) != 0)
      scene_views_.at(curr_scene)->Render();
  }
}
