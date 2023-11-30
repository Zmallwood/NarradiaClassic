#include "Game.h"
#include "core/controller/EngineController.h"
#include "core/model/Engine.h"
#include "core/view/EngineView.h"

namespace Narradia {
    /**
     * Run a new game instance.
     */
    void Game::Run() {
        while (Engine::Get()->is_running()) {
            EngineController::Get()->HandleInput();
            EngineController::Get()->UpdateGameFlow();
            Engine::Get()->UpdateGameLogic();
            EngineView::Get()->Render();
        }
        DisposeAllSingletons();
    }
}
