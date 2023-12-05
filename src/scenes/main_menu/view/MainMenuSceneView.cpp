#include "MainMenuSceneView.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"
#include "scenes/main_menu/model/MainMenuScene.h"

namespace Narradia {
    MainMenuSceneView::MainMenuSceneView() {
        scene_gui_view()->set_scene_gui(MainMenuScene::Get()->scene_gui());
        rid_box = Renderer2DSolidColorsView::Get()->NewRect();
        rid_background = Renderer2DImagesView::Get()->NewImage();
    }

    /**
     * Render operations.
     */
    void MainMenuSceneView::RenderDerived() {
        Renderer2DImagesView::Get()->DrawImage(
            "DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
        RectF rect = {0.15f, 0.15f, 0.2f, 0.1f};
        Color color = {0, 0, 255, 255};
        Renderer2DSolidColorsView::Get()->FillRect(rid_box, rect, color);
    }
}
