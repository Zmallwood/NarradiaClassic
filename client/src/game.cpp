#include "game.h"
#include "core/controller/engine_controller.h"
#include "core/model/engine.h"
#include "core/model/fps_capper.h"
#include "core/view/engine_view.h"
namespace Narradia
{
    /**
     Run a new game instance.
    */
    void Game::Run() {
        while (Engine::get()->is_running()) {
            if (FPSCapper::get()->RunningBelow60FPS()) {
                EngineController::get()->HandleInput();
                EngineController::get()->UpdateGameFlow();
                Engine::get()->UpdateGameLogic();
                EngineView::get()->Render();
            }
        }
        DisposeAllSingletons();
    }
}
