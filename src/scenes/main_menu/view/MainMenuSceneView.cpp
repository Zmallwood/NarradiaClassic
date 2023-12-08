#include "MainMenuSceneView.h"
#include "core.gui/view/GuiButtonView.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "scenes/main_menu/model/MainMenuScene.h"

namespace Narradia {
    /**
     * Set scene gui and initialize Views for gui components initialize in scene
     * model. Also prepare RenderIDs for images to be rendered.
     */
    MainMenuSceneView::MainMenuSceneView() {
        scene_gui_view_->set_scene_gui(MainMenuScene::Get()->scene_gui());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        rid_background = Renderer2DImagesView::Get()->NewImage();
        rid_logo = Renderer2DImagesView::Get()->NewImage();
    }

    /**
     * Render operations.
     */
    void MainMenuSceneView::RenderDerived() {
        Renderer2DImagesView::Get()->DrawImage(
            "DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
        Renderer2DImagesView::Get()->DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
        RectF rect = {0.15f, 0.15f, 0.2f, 0.1f};
        Color color = {0, 0, 255, 255};
    }
}
