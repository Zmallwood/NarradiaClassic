#include "MainSceneView.h"
#include "main_scene.modules/view/WorldDisplayModuleView.h"

namespace Narradia {
    /**
     * Render operations.
     */
    void MainSceneView::RenderDerived() {
        WorldDisplayModuleView::Get()->Render();
    }
}
