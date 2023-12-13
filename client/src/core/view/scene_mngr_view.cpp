#include "scene_mngr_view.h"
namespace Narradia
{
   SceneMngrView::SceneMngrView() {
      scene_views_[SceneNames::Intro] = IntroSceneView::get();
      scene_views_[SceneNames::MainMenu] = MainMenuSceneView::get();
      scene_views_[SceneNames::Main] = MainSceneView::get();
   }

   auto SceneMngrView::RenderCurrScene() -> void {
      auto curr_scene = SceneMngr::get()->curr_scene();
      if (scene_views_.count(curr_scene) != 0)
         scene_views_.at(curr_scene)->Render();
   }
}
