#if 1
#include "pages_v.h"
#include "pages.h"
#include "gui-core_v.h"
#include "rend_2d_images_v.h"
#include "rend_text.h"
#include "gui-core_v.h"
#include "main_menu_pg-adds-menu_models_v.h"
#include "map_creation_pg-adds-map_gen_v.h"
#include "actors.h"
#include "main_pg-adds-visual_v.h"
#include "main_pg-adds-world_view_v.h"
#include "main_pg-gui_comps_v.h"
#include "main_pg-gui_windows_v.h"
#endif

namespace Narradia
{
   // IntroPgV
#if 1
   IntroPgV::IntroPgV() {
      scene_gui_view_->set_scene_gui(IntroPg::get()->scene_gui());
      rid_background = NewImage();
      rid_logo = NewImage();
      rid_text = NewString();
   }
   void IntroPgV::RenderDerived() {
      RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};
      DrawImage("DefaultSceneBackground", rid_background, dest_background);
      DrawImage("NarradiaLogo", rid_logo, {0.3f, 0.1f, 0.4f, 0.2f});
      RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
      Color color = {1.0f, 0.0f, 0.0f, 255};
      if (SDL_GetTicks() % 600 > 300)
         DrawString(rid_text, "Press to start", {0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, true);
   }
#endif

   // MainMenuPgV
#if 1
   MainMenuPgV::MainMenuPgV() {
      scene_gui_view_->set_scene_gui(MainMenuPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      rid_background = NewImage();
      rid_logo = NewImage();
   }
   void MainMenuPgV::RenderDerived() {
      DrawImage("DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
      DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
      MenuModelsAddV::get()->Render();
   }
#endif

   // MapCreationPgV
#if 1
   void MapCreationPgV::RenderDerived() {
      MapGenAddV::get()->Render();
   }
#endif

   // MainPgV
#if 1
   MainPgV::MainPgV() {
      scene_gui_view_->set_scene_gui(MainPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<ExperienceBarV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<StatusPanelV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiWindowWorldMapV>());
   }
   void MainPgV::RenderDerived() {
      WorldViewAddV::get()->Render();
      FPSCounterAddV::get()->Render();
   }
#endif
}

