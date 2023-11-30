#include "EngineController.h"
#include "SceneMngrController.h"
#include "functions/DoPollEvents.h"

namespace Narradia {
    /**
     * Handle user input every frame.
     */
    void EngineController::HandleInput() {
        DoPollEvents();
    }

    /**
     * Update game flow between scenes every frame.
     */
    void EngineController::UpdateGameFlow() {
        SceneMngrController::Get()->UpdateGameFlowCurrScene();
    }
}
