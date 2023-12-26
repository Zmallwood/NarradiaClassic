#include "main_scene.h"
#include "../../../core-gui/m/scene_gui.h"
#include "../../../main_scene-modules/m/kb_bindings_module.h"
#include "../../../main_scene-modules/m/mob_movement_module.h"
#include "main_scene-gui/m/experience_bar.h"
#include "main_scene-gui/m/gui_window_world_map.h"
#include "main_scene-gui/m/status_panel.h"
#include "main_scene-modules-world_view/m/world_view_module.h"
#include "main_scene-modules/m/combat_chase_movement_module.h"
#include "main_scene-modules/m/combat_module.h"
#include "main_scene-modules/m/fps_counter_module.h"
#include "main_scene-modules/m/keyboard_movement_module.h"
#include "main_scene-modules/m/mob_death_handling_module.h"
#include "main_scene-modules/m/mob_targeting_module.h"
#include "main_scene-modules/m/mouse_movement_module.h"
#include "main_scene-modules/m/mouse_rotation_module.h"
#include "main_scene-modules/m/skill_performing_module.h"
#include "main_scene-modules/m/tile_hovering_module.h"
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
