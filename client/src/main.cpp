#if 1
#include "core.h"
#include "core_c.h"
#include "core_v.h"
#endif

int main(int argc, char *argv[]) {
   using namespace Narradia;

   while (Engine::get()->is_running()) {
      if (FPSCapper::get()->Below60FPS()) {
         try {
            EngineC::get()->HandleInput();
            EngineC::get()->UpdateGameFlow();
            Engine::get()->UpdateGameLogic();
            EngineV::get()->Render();
            Engine::get()->Finalize();
         }
         catch (std::exception &e) {
            Console::get()->Print("Exception in main: " + std::string(e.what()));
         }
      }
   }

   DisposeSingletons();
}
