#include "MainSceneView.h"
#include "main_scene.modules/view/WorldViewModuleView.h"
#include "scenes/main/model/MainScene.h"

namespace Narradia {
    MainSceneView::MainSceneView() {
        scene_gui_view_->set_scene_gui(MainScene::Get()->scene_gui());
    }

    /**
     * Render operations.
     */
    void MainSceneView::RenderDerived() {
        WorldViewModuleView::Get()->Render();
    }
}
