#if 1
#include "main_pg.h"
#include "main_pg-gui_comps.h"
#include "main_pg-gui_windows.h"
#include "main_pg-adds-non-visual.h"
#include "main_pg-adds-visual.h"
#include "main_pg-adds-world_view.h"
#endif

namespace Narradia
{
   MainPg::MainPg()
   {
      scene_gui()->AddGuiComponent(std::make_shared<ExperienceBar>());
      scene_gui()->AddGuiComponent(std::make_shared<StatusPanel>());
      scene_gui()->AddGuiComponent(GuiWindowWorldMap::get());
   }
   void MainPg::UpdateGameLogicDerived()
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
