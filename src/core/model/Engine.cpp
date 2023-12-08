#include "Engine.h"
#include "SceneMngr.h"
#include "core.input/model/MouseInput.h"

namespace Narradia {
    /**
     * Seeds the randomization to get unique random generations each game start.
     */
    Engine::Engine() {
        srand(time(nullptr));
    }

    /**
     * Update game logic for current frame.
     */
    void Engine::UpdateGameLogic() {
        SceneMngr::Get()->UpdateGameLogicCurrScene();
        MouseInput::Get()->PerformMouseActions();
    }
}
