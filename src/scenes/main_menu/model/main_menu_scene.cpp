#include "main_menu_scene.h"
#include "core.gui/model/gui_button.h"
#include "core/controller/scene_mngr_controller.h"
#include "core/model/engine.h"

namespace Narradia {
  /**
   Initialize GuiComponents.
  */
  MainMenuScene::MainMenuScene() {
    scene_gui()->AddGuiComponent(
        std::make_shared<GuiButton>("Play", RectF{0.4f, 0.4f, 0.2f, 0.1f}, [] {
          SceneMngrController::Get()->ChangeScene(SceneNames::Main);
        }));
    scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
        "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f}, [] { Engine::Get()->set_running(false); }));
  }

  /**
   Update game logic.
  */
  void MainMenuScene::UpdateGameLogicDerived() {
  }
}
