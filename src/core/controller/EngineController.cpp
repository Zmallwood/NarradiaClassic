#include "EngineController.h"
#include "SceneMngrController.h"
#include "functions/PollEvents.h"

namespace Narradia
{
    /**
     * Handle user input every frame.
     */
    void EngineController::HandleInput() {

        PollEvents();
    }

    /**
     * Update game flow between scenes every frame.
     */
    void EngineController::UpdateGameFlow() {

        SceneMngrController::Get()->UpdateGameFlowCurrScene();
    }
}
