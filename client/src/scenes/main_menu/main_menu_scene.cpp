#if 1
#include "main_menu_scene.h"
#include "gui-core/gui_button.h"
#include "core/scene_mngr_c.h"
#include "core/engine.h"
#include "model_display_module.h"
#include "gui-core/scene_gui.h"
#endif

namespace Narradia
{
   MainMenuScene::MainMenuScene()
   {
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Play", RectF{0.4f, 0.4f, 0.2f, 0.1f},
          [] { SceneMngrC::get()->ChangeScene(SceneNames::MapOverviewGen); }));
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f}, [] { Engine::get()->set_running(false); }));
   }
   void MainMenuScene::UpdateGameLogicDerived()
   {
      ModelDisplayModule::get()->UpdateGameLogic();
   }
}
