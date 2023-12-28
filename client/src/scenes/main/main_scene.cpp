#if 1
#include "main_scene.h"
#include "main_scene-gui_components.h"
#include "main_scene-gui_windows.h"
#include "main_scene-adds-non-visible.h"
#include "main_scene-adds-visible.h"
#include "main_scene-adds-world_view_module.h"
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
