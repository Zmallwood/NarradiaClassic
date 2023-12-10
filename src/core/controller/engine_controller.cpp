#include "engine_controller.h"
#include "scene_mngr_controller.h"
#include "command/poll_events.h"
namespace Narradia {
  /**
   Handle user input every frame.
  */
  void EngineController::HandleInput() {
    PollEvents();
  }

  /**
   Update game flow between scenes every frame.
  */
  void EngineController::UpdateGameFlow() {
    SceneMngrController::Get()->UpdateGameFlowCurrScene();
  }
}
