#include "MainMenuScene.h"
#include "core.gui/model/GuiButton.h"
#include "core/controller/SceneMngrController.h"
#include "core/model/Engine.h"

namespace Narradia {
    MainMenuScene::MainMenuScene() {
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Play 2D", RectF{0.4f, 0.25f, 0.2f, 0.1f}, [] {
                SceneMngrController::Get()->ChangeScene(SceneNames::Main2D);
            }));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Play 3D", RectF{0.4f, 0.4f, 0.2f, 0.1f}, [] {
                SceneMngrController::Get()->ChangeScene(SceneNames::Main3D);
            }));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Exit", RectF{0.4f, 0.55f, 0.2f, 0.1f},
            [] { Engine::Get()->set_running(false); }));
    }

    /**
     * Update game logic.
     */
    void MainMenuScene::UpdateGameLogicDerived() {
    }
}
