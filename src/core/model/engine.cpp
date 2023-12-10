#include "engine.h"
#include "cursor.h"
#include "scene_mngr.h"
#include "core.input/model/mouse_input.h"
namespace Narradia {
  /**
   Seeds the randomization to get unique random
   generations each game start.
  */
  Engine::Engine() {
    srand(time(nullptr));
  }

  /**
   Update game logic for current frame.
  */
  void Engine::UpdateGameLogic() {
    Cursor::Get()->ResetStyle();
    SceneMngr::Get()->UpdateGameLogicCurrScene();
    MouseInput::Get()->PerformMouseActions();
  }
}
