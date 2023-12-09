#include "Game.h"
#include "core/controller/EngineController.h"
#include "core/model/Engine.h"
#include "core/model/FPSCapper.h"
#include "core/view/EngineView.h"

namespace Narradia
{
    /**
     Run a new game instance.
    */
    void Game::Run()
    {
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
