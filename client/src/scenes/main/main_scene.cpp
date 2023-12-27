#if 1
#include "main_scene.h"
#include "main_scene-modules/kb_bindings_module.h"
#include "main_scene-modules/mob_movement_module.h"
#include "main_scene-gui/experience_bar.h"
#include "main_scene-gui/gui_window_world_map.h"
#include "main_scene-gui/status_panel.h"
#include "main_scene-modules-world_view/world_view_module.h"
#include "main_scene-modules/combat_chase_movement_module.h"
#include "main_scene-modules/combat_module.h"
#include "main_scene-modules/fps_counter_module.h"
#include "main_scene-modules/keyboard_movement_module.h"
#include "main_scene-modules/mob_death_handling_module.h"
#include "main_scene-modules/mob_targeting_module.h"
#include "main_scene-modules/mouse_movement_module.h"
#include "main_scene-modules/mouse_rotation_module.h"
#include "main_scene-modules/skill_performing_module.h"
#include "main_scene-modules/tile_hovering_module.h"
#endif

namespace Narradia
{
   MainScene::MainScene()
   {
      scene_gui()->AddGuiComponent(std::make_shared<ExperienceBar>());
      scene_gui()->AddGuiComponent(std::make_shared<StatusPanel>());
      scene_gui()->AddGuiComponent(GuiWindowWorldMap::get());
   }
   void MainScene::UpdateGameLogicDerived()
   {
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
