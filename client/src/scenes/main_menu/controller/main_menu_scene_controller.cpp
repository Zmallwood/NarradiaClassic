#include "main_menu_scene_controller.h"
#include "core-assets/model/model_bank.h"
#include "core-render-models/view/command/new_model.h"
namespace Narradia
{
    /**
     On entering scene.
    */
    void MainMenuSceneController::OnEnter() {
        auto all_models = *ModelBank::get()->models();
        for (auto &entry : all_models)
            NewModel(entry.first);
    }

    /**
     Update game flow between scenes.
    */
    void MainMenuSceneController::UpdateGameFlowDerived() {
    }
}
