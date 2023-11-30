#include "Engine.h"
#include "SceneMngr.h"

namespace Narradia {
    Engine::Engine() {
        srand(time(nullptr));
    }

    /**
     * Update game logic for current frame.
     */
    void Engine::UpdateGameLogic() {
        SceneMngr::Get()->UpdateGameLogicCurrScene();
    }
}
