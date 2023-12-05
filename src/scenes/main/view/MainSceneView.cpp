#include "MainSceneView.h"
#include "main_scene.modules/view/WorldDisplayModuleView.h"
#include "main_scene.modules/view/FPSCounterModuleView.h"

namespace Narradia {
    /**
     * Render operations.
     */
    void MainSceneView::RenderDerived() {
        WorldDisplayModuleView::Get()->Render();
        FPSCounterModuleView::Get()->Render();
    }
}
