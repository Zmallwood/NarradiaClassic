#include "Engine.h"
#include "Cursor.h"
#include "SceneMngr.h"
#include "core.input/model/MouseInput.h"

namespace Narradia
{
    /**
    Seeds the randomization to get unique random generations each game start.
    */
    Engine::Engine() { srand(time(nullptr)); }

    /**
    Update game logic for current frame.
    */
    void Engine::UpdateGameLogic()
    {
        Cursor::Get()->ResetStyle();
        SceneMngr::Get()->UpdateGameLogicCurrScene();
        MouseInput::Get()->PerformMouseActions();
    }
}
