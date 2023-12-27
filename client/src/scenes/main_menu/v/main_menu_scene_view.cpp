#include "main_menu_scene_view.h"
#include "gui-core/v/gui_button_view.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "model_display_module_view.h"
#include "scenes/main_menu/m/main_menu_scene.h"

namespace Narradia
{
   MainMenuSceneView::MainMenuSceneView()
   {
      scene_gui_view_->set_scene_gui(MainMenuScene::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
      scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
      rid_background = NewImage();
      rid_logo = NewImage();
   }

   void MainMenuSceneView::RenderDerived()
   {
      DrawImage("DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
      DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
      ModelDisplayModuleView::get()->Render();
   }
}
