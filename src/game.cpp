#include "game.h"
#include "core/controller/engine_controller.h"
#include "core/model/engine.h"
#include "core/model/fps_capper.h"
#include "core/view/engine_view.h"

namespace Narradia {
  /**
   Run a new game instance.
  */
  void Game::Run() {
    while (Engine::Get()->is_running()) {
      if (FPSCapper::Get()->RunningBelow60FPS()) {
        EngineController::Get()->HandleInput();
        EngineController::Get()->UpdateGameFlow();
        Engine::Get()->UpdateGameLogic();
        EngineView::Get()->Render();
      }
    }
    DisposeAllSingletons();
  }
}
