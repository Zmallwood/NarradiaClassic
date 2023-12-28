#if 1
#include "main_scene_c.h"
#include "main_scene-modules/player_spawn_positioning_module.h"
#endif

namespace Narradia
{
   void MainSceneC::OnEnter()
   {
      Console::get()->Print("Entering Narradia");
      PlayerSpawnPositioningModule::get()->SpawnAtGoodLocation();
   }
   void MainSceneC::UpdateGameFlowDerived()
   {
   }
}
