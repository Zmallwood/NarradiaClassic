#include "main_scene.h"
#include "main_scene.modules.world_view/model/world_view_module.h"
#include "main_scene.modules/model/fps_counter_module.h"
#include "main_scene.modules/model/keyboard_movement_module.h"
#include "main_scene.modules/model/mob_movement_module.h"
#include "main_scene.modules/model/mouse_rotation_module.h"
#include "main_scene.modules/model/tile_hovering_module.h"

namespace Narradia {
  /**
   Update game logic.
  */
  void MainScene::UpdateGameLogicDerived() {
    MobMovementModule::Get()->UpdateGameLogic();
    KeyboardMovementModule::Get()->UpdateGameLogic();
    WorldViewModule::Get()->UpdateGameLogic();
    MouseRotationModule::Get()->UpdateGameLogic();
    TileHoveringModule::Get()->UpdateGameLogic();
    FPSCounterModule::Get()->UpdateGameLogic();
  }
}
