#if 1
#include "game.h"
#include "core/c/engine_controller.h"
#include "core/m/engine.h"
#include "core/m/fps_capper.h"
#include "core/v/engine_view.h"
#endif
namespace Narradia
{
   void Game::Run()
   {
      while (Engine::get()->is_running())
      {
         if (FPSCapper::get()->RunningBelow60FPS())
         {
            EngineController::get()->HandleInput();
            EngineController::get()->UpdateGameFlow();
            Engine::get()->UpdateGameLogic();
            EngineView::get()->Render();
            Engine::get()->Finalize();
         }
      }
      DisposeAllStons();
   }
}
