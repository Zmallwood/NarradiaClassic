#include "world_view_module.h"
#include "camera.h"
#include "core.assets/model/model_bank.h"
#include "core.render/view/renderer_models_view.h"
namespace Narradia
{
    WorldViewModule::WorldViewModule() {
        auto all_models = *ModelBank::get()->models();
        for (auto &entry : all_models)
            RendererModelsView::get()->NewModel(entry.first);
    }

    void WorldViewModule::UpdateGameLogic() {
        Camera::get()->UpdateGameLogic();
    }
}
