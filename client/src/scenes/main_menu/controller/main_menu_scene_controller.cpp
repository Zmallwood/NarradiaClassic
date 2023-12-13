#include "main_menu_scene_controller.h"
#include "core.assets/model/model_bank.h"
#include "core.render/view/renderer_models_view.h"
namespace Narradia
{
    /**
     On entering scene.
    */
    void MainMenuSceneController::OnEnter() {
        auto all_models = *ModelBank::get()->models();
        for (auto &entry : all_models)
            RendererModelsView::get()->NewModel(entry.first);
    }

    /**
     Update game flow between scenes.
    */
    void MainMenuSceneController::UpdateGameFlowDerived() {
    }
}
