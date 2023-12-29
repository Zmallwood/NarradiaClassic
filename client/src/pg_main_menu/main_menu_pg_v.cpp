#if 1
#include "main_menu_pg_v.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#include "model_display_add_v.h"
#include "main_menu_pg.h"
#include "gui-core_v.h"
#endif

namespace Narradia
{
   MainMenuPgV::MainMenuPgV()
   {
      scene_gui_view_->set_scene_gui(MainMenuPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      rid_background = NewImage();
      rid_logo = NewImage();
   }
   void MainMenuPgV::RenderDerived()
   {
      DrawImage("DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
      DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
      ModelDisplayAddV::get()->Render();
   }
}
