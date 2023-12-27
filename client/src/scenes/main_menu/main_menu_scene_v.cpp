#if 1
#include "main_menu_scene_v.h"
#include "gui-core/gui_button_v.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#include "model_display_module_v.h"
#include "scenes/main_menu/main_menu_scene.h"
#include "gui-core/scene_gui_v.h"
#endif

namespace Narradia
{
   MainMenuSceneV::MainMenuSceneV()
   {
      scene_gui_view_->set_scene_gui(MainMenuScene::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonV>());
      rid_background = NewImage();
      rid_logo = NewImage();
   }
   void MainMenuSceneV::RenderDerived()
   {
      DrawImage("DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
      DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
      ModelDisplayModuleV::get()->Render();
   }
}
