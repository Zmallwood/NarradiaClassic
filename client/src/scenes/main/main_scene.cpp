#if 1
#include "main_scene.h"
#include "main_scene-gui_comps.h"
#include "main_scene-gui_windows.h"
#include "main_scene-adds-non-visual.h"
#include "main_scene-adds-visual.h"
#include "main_scene-adds-world_view_add.h"
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
      KbBindingsAdd::get()->UpdateGameLogic();
      MobMovementAdd::get()->UpdateGameLogic();
      KeyboardMovementAdd::get()->UpdateGameLogic();
      MouseMovementAdd::get()->UpdateGameLogic();
      CombatChaseMovementAdd::get()->UpdateGameLogic();
      WorldViewAdd::get()->UpdateGameLogic();
      MouseRotationAdd::get()->UpdateGameLogic();
      TileHoveringAdd::get()->UpdateGameLogic();
      MobTargetingAdd::get()->UpdateGameLogic();
      CombatAdd::get()->UpdateGameLogic();
      SkillPerformingAdd::get()->UpdateGameLogic();
      MobDeathHandlingAdd::get()->UpdateGameLogic();
      FPSCounterAdd::get()->UpdateGameLogic();
   }
}
