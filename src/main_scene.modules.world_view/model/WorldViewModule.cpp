#include "WorldViewModule.h"
#include "Camera.h"
#include "core.assets/model/ModelBank.h"

namespace Narradia {
    WorldViewModule::WorldViewModule() {
        auto all_models = ModelBank::Get()->models();
    }

    void WorldViewModule::UpdateGameLogic() {
        Camera::Get()->UpdateGameLogic();
    }
}
