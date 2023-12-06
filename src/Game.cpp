#include "Game.h"
#include "core/controller/EngineController.h"
#include "core/model/Engine.h"
#include "core/view/EngineView.h"

namespace Narradia {
    /**
     * Run a new game instance.
     */
    void Game::Run() {
        auto a = 0;
        auto b = 0;
        auto delta = 0;
        while (Engine::Get()->is_running()) {
            a = SDL_GetTicks();
            delta = a - b;
            if (delta > 1000 / 60.0f) {
                b = a;
                EngineController::Get()->HandleInput();
                EngineController::Get()->UpdateGameFlow();
                Engine::Get()->UpdateGameLogic();
                EngineView::Get()->Render();
            }
        }
        DisposeAllSingletons();
    }
}
