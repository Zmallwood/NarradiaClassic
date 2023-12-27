#if 1
#include "engine_controller.h"
#include "cmd/poll_events.h"
#include "scene_mngr_controller.h"
#endif

namespace Narradia
{
   auto EngineController::HandleInput() -> void
   {
      PollEvents();
   }

   auto EngineController::UpdateGameFlow() -> void
   {
      SceneMngrController::get()->UpdateGameFlowCurrScene();
   }
}
