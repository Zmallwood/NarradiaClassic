#include "main_scene.h"
#include "main_scene-gui/model/experience_bar.h"
#include "main_scene-gui/model/gui_window_world_map.h"
#include "main_scene-gui/model/status_panel.h"
#include "main_scene-modules-world_view/model/world_view_module.h"
#include "main_scene-modules/model/combat_chase_movement_module.h"
#include "main_scene-modules/model/combat_module.h"
#include "main_scene-modules/model/fps_counter_module.h"
#include "main_scene-modules/model/kb_bindings_module.h"
#include "main_scene-modules/model/keyboard_movement_module.h"
#include "main_scene-modules/model/mob_death_handling_module.h"
#include "main_scene-modules/model/mob_movement_module.h"
#include "main_scene-modules/model/mob_targeting_module.h"
#include "main_scene-modules/model/mouse_movement_module.h"
#include "main_scene-modules/model/mouse_rotation_module.h"
#include "main_scene-modules/model/skill_performing_module.h"
#include "main_scene-modules/model/tile_hovering_module.h"
namespace Narradia
{
   MainScene::MainScene() {
      scene_gui()->AddGuiComponent(std::make_shared<ExperienceBar>());
      scene_gui()->AddGuiComponent(std::make_shared<StatusPanel>());
      scene_gui()->AddGuiComponent(GuiWindowWorldMap::get());
   }

   /**
    Update game logic.
   */
   void MainScene::UpdateGameLogicDerived() {
      KbBindingsModule::get()->UpdateGameLogic();
      MobMovementModule::get()->UpdateGameLogic();
      KeyboardMovementModule::get()->UpdateGameLogic();
      MouseMovementModule::get()->UpdateGameLogic();
      CombatChaseMovementModule::get()->UpdateGameLogic();
      WorldViewModule::get()->UpdateGameLogic();
      MouseRotationModule::get()->UpdateGameLogic();
      TileHoveringModule::get()->UpdateGameLogic();
      MobTargetingModule::get()->UpdateGameLogic();
      CombatModule::get()->UpdateGameLogic();
      SkillPerformingModule::get()->UpdateGameLogic();
      MobDeathHandlingModule::get()->UpdateGameLogic();
      FPSCounterModule::get()->UpdateGameLogic();
   }
}
