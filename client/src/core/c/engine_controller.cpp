#include "engine_controller.h"

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
