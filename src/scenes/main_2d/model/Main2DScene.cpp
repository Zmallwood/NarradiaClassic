#include "Main2DScene.h"
#include "core.gui/model/GuiButton.h"
#include "main_scene.modules/model/FPSCounterModule.h"
#include "main_2d_scene.modules/model/KeyboardMovementModule.h"
#include "main_2d_scene.modules/model/MobMovementModule.h"
#include "main_2d_scene.modules/model/MouseMovementModule.h"
#include "main_2d_scene.modules/model/TileHoveringModule.h"
#include "main_2d_scene.modules/model/CombatModule.h"
#include "main_2d_scene.modules/model/MobTargetingModule.h"
#include "main_2d_scene.modules/model/CombatChaseMovementModule.h"
#include "main_2d_scene.modules/model/MobDeathHandlingModule.h"
#include "main_2d_scene.modules/model/SkillPerformingModule.h"

namespace Narradia {
    /**
     * Initialize GUI components.
     */
    Main2DScene::Main2DScene() {
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Char", RectF{0.75f, 0.96f, 0.05f, 0.04f}, [] {}));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Inv", RectF{0.8f, 0.96f, 0.05f, 0.04f}, [] {}));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Skill", RectF{0.85f, 0.96f, 0.05f, 0.04f}, [] {}));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Rep", RectF{0.9f, 0.96f, 0.05f, 0.04f}, [] {}));
        scene_gui()->AddGuiComponent(std::make_shared<GuiButton>(
            "Sys", RectF{0.95f, 0.96f, 0.05f, 0.04f}, [] {}));
    }

    /**
     * Update game logic.
     */
    void Main2DScene::UpdateGameLogicDerived() {
        KeyboardMovementModule::Get()->UpdateGameLogic();
        MouseMovementModule::Get()->UpdateGameLogic();
        TileHoveringModule::Get()->UpdateGameLogic();
        MobMovementModule::Get()->UpdateGameLogic();
        MobTargetingModule::Get()->UpdateGameLogic();
        CombatChaseMovementModule::Get()->UpdateGameLogic();
        CombatModule::Get()->UpdateGameLogic();
        MobDeathHandlingModule::Get()->UpdateGameLogic();
        SkillPerformingModule::Get()->UpdateGameLogic();
        FPSCounterModule::Get()->UpdateGameLogic();
    }
}
