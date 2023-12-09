#include "WorldViewModule.h"
#include "Camera.h"
#include "core.assets/model/ModelBank.h"
#include "core.render/view/RendererModelsView.h"

namespace Narradia {
    WorldViewModule::WorldViewModule() {
        auto all_models = *ModelBank::Get()->models();
        for (auto &entry : all_models)
            RendererModelsView::Get()->NewModel(entry.first);
    }

    void WorldViewModule::UpdateGameLogic() {
        Camera::Get()->UpdateGameLogic();
    }
}
