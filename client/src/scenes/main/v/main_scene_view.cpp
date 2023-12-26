#include "main_scene_view.h"
#include "core-render-text/v/cmd/draw_string.h"
#include "core-render-text/v/cmd/new_string.h"
#include "main_scene-gui/v/experience_bar_view.h"
#include "main_scene-gui/v/gui_window_world_map_view.h"
#include "main_scene-gui/v/status_panel_view.h"
#include "main_scene-modules-world_view/v/world_view_module_view.h"
#include "main_scene-modules/v/fps_counter_module_view.h"
#include "scenes/main/m/main_scene.h"
#include "world-actors/m/player.h"
namespace Narradia
{
   MainSceneView::MainSceneView()
   {
      scene_gui_view_->set_scene_gui(MainScene::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<ExperienceBarView>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<StatusPanelView>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiWindowWorldMapView>());
   }

   /**
    Render operations.
   */
   void MainSceneView::RenderDerived()
   {
      WorldViewModuleView::get()->Render();
      FPSCounterModuleView::get()->Render();
   }
}
