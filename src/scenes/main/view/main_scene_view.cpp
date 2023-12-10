#include "main_scene_view.h"
#include "main_scene.modules.world_view/view/world_view_module_view.h"
#include "main_scene.modules/view/fps_counter_module_view.h"
#include "scenes/main/model/main_scene.h"
namespace Narradia {
  MainSceneView::MainSceneView() {
    scene_gui_view_->set_scene_gui(MainScene::Get()->scene_gui());
  }

  /**
   Render operations.
  */
  void MainSceneView::RenderDerived() {
    WorldViewModuleView::Get()->Render();
    FPSCounterModuleView::Get()->Render();
  }
}
