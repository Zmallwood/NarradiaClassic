#if 1
#include "main_scene_v.h"
#include "main_scene-gui_windows_v.h"
#include "main_scene-adds-world_view_add_v.h"
#include "main_scene-gui_comps_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "main_scene-adds-visual_v.h"
#include "render-text/cmd_v/new_string.h"
#include "scenes/main/main_scene.h"
#include "actors.h"
#endif

namespace Narradia
{
   MainSceneV::MainSceneV()
   {
      scene_gui_view_->set_scene_gui(MainScene::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<ExperienceBarV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<StatusPanelV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiWindowWorldMapV>());
   }
   void MainSceneV::RenderDerived()
   {
      WorldViewAddV::get()->Render();
      FPSCounterAddV::get()->Render();
   }
}
