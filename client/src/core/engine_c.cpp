#if 1
#include "engine_c.h"
#include "cmd_c/poll_events.h"
#include "scene_mngr_c.h"
#endif

namespace Narradia
{
   auto EngineC::HandleInput() -> void
   {
      PollEvents();
   }
   auto EngineC::UpdateGameFlow() -> void
   {
      SceneMngrC::get()->UpdateGameFlowCurrScene();
   }
}
