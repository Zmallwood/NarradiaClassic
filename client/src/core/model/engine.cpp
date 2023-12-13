#include "engine.h"
namespace Narradia
{
   Engine::Engine() {
      srand(time(nullptr));
   }

   void Engine::UpdateGameLogic() {
      Cursor::get()->ResetStyle();
      SceneMngr::get()->UpdateGameLogicCurrScene();
      MouseInput::get()->PerformMouseActions();
   }
}