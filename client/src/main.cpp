#if 1
#include "core/engine_c.h"
#include "core/engine.h"
#include "core/fps_capper.h"
#include "core/engine_v.h"
#endif

int main(int argc, char *argv[])
{
   using namespace Narradia;

   while (Engine::get()->is_running())
   {
      if (FPSCapper::get()->RunningBelow60FPS())
      {
         EngineC::get()->HandleInput();
         EngineC::get()->UpdateGameFlow();
         Engine::get()->UpdateGameLogic();
         EngineV::get()->Render();
         Engine::get()->Finalize();
      }
   }

   DisposeAllStons();
}
