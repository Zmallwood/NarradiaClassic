#include "Main2DSceneView.h"
#include "core.gui/view/GuiButtonView.h"
#include "main_2d_scene.modules/view/FPSCounterModuleView.h"
#include "main_2d_scene.modules/view/WorldDisplayModuleView.h"
#include "scenes/main_2d/model/Main2DScene.h"

namespace Narradia {
    /**
     * Set scene gui and initialize Views for gui components initialized in
     * scene model.
     */
    Main2DSceneView::Main2DSceneView() {
        scene_gui_view_->set_scene_gui(Main2DScene::Get()->scene_gui());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
    }

    /**
     * Render operations.
     */
    void Main2DSceneView::RenderDerived() {
        WorldDisplayModuleView::Get()->Render();
        FPSCounterModuleView::Get()->Render();
    }
}
