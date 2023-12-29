#if 1
#include "main_pg_v.h"
#include "main_pg-gui_windows_v.h"
#include "main_pg-adds-world_view_v.h"
#include "main_pg-gui_comps_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "main_pg-adds-visual_v.h"
#include "render-text/cmd_v/new_string.h"
#include "main_pg.h"
#include "actors.h"
#endif

namespace Narradia
{
   MainPgV::MainPgV()
   {
      scene_gui_view_->set_scene_gui(MainPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<ExperienceBarV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<StatusPanelV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiWindowWorldMapV>());
   }
   void MainPgV::RenderDerived()
   {
      WorldViewAddV::get()->Render();
      FPSCounterAddV::get()->Render();
   }
}
