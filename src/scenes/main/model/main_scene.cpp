#include "main_scene.h"
#include "main_scene.modules.world_view/model/world_view_module.h"
#include "main_scene.modules/model/fps_counter_module.h"
#include "main_scene.modules/model/keyboard_movement_module.h"
#include "main_scene.modules/model/mob_movement_module.h"
#include "main_scene.modules/model/mouse_rotation_module.h"
#include "main_scene.modules/model/tile_hovering_module.h"
#include "main_scene.modules/model/mouse_movement_module.h"
#include "main_scene.modules/model/mob_targeting_module.h"
#include "main_scene.modules/model/combat_chase_movement_module.h"
#include "main_scene.modules/model/combat_module.h"
#include "main_scene.modules/model/mob_death_handling_module.h"
#include "main_scene.modules/model/skill_performing_module.h"
namespace Narradia {
  /**
   Update game logic.
  */
  void MainScene::UpdateGameLogicDerived() {
    MobMovementModule::Get()->UpdateGameLogic();
    KeyboardMovementModule::Get()->UpdateGameLogic();
    MouseMovementModule::Get()->UpdateGameLogic();
    CombatChaseMovementModule::Get()->UpdateGameLogic();
    WorldViewModule::Get()->UpdateGameLogic();
    MouseRotationModule::Get()->UpdateGameLogic();
    TileHoveringModule::Get()->UpdateGameLogic();
    MobTargetingModule::Get()->UpdateGameLogic();
    CombatModule::Get()->UpdateGameLogic();
    SkillPerformingModule::Get()->UpdateGameLogic();
    MobDeathHandlingModule::Get()->UpdateGameLogic();
    FPSCounterModule::Get()->UpdateGameLogic();
  }
}
