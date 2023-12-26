#include "main_menu_scene.h"
#include "core-gui/m/gui_button.h"
#include "core/c/scene_mngr_controller.h"
#include "core/m/engine.h"
#include "model_display_module.h"
namespace Narradia
{
   /**
    Initialize GuiComponents.
   */
   MainMenuScene::MainMenuScene()
   {
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Play", RectF{0.4f, 0.4f, 0.2f, 0.1f},
          [] { SceneMngrController::get()->ChangeScene(SceneNames::MapOverviewGen); }));
      scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
          "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f}, [] { Engine::get()->set_running(false); }));
   }

   /**
    Update game logic.
   */
   void MainMenuScene::UpdateGameLogicDerived()
   {
      ModelDisplayModule::get()->UpdateGameLogic();
   }
}
