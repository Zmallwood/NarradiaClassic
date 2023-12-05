#include "MainMenuScene.h"
#include "core.gui/model/GuiButton.h"

namespace Narradia {
    MainMenuScene::MainMenuScene() {
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Play", RectF{0.1f, 0.1f, 0.2f, 0.1f}, [] {}));
    }

    /**
     * Update game logic.
     */
    void MainMenuScene::UpdateGameLogicDerived() {
    }
}
