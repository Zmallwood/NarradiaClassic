#if 1
#include "main_pg_c.h"
#include "main_pg-adds-non-visual.h"
#endif

namespace Narradia
{
   void MainPgC::OnEnter()
   {
      Console::get()->Print("Entering Narradia");
      PlayerSpawnPositioningAdd::get()->SpawnAtGoodLocation();
   }
   void MainPgC::UpdateGameFlowDerived()
   {
   }
}
