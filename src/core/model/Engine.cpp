#include "Engine.h"
#include "SceneMngr.h"
#include "core.input/model/MouseInput.h"

namespace Narradia {
    Engine::Engine() {
        srand(time(nullptr));
    }

    /**
     * Update game logic for current frame.
     */
    void Engine::UpdateGameLogic() {
        SceneMngr::Get()->UpdateGameLogicCurrScene();
        MouseInput::Get()->PerformMouseActions();
        MouseInput::Get()->Reset();
    }
}
