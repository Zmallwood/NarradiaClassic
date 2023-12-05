#include "IntroSceneView.h"
#include "core.render.text/view/RendererText.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"
#include "scenes/intro/model/IntroScene.h"

namespace Narradia {
    IntroSceneView::IntroSceneView() {
        scene_gui_view()->set_scene_gui(IntroScene::Get()->scene_gui());
        rid_box = Renderer2DSolidColorsView::Get()->NewRect();
        rid_background = Renderer2DImagesView::Get()->NewImage();
        rid_text = RendererText::Get()->NewString();
    }

    /**
     * Render operations.
     */
    void IntroSceneView::RenderDerived() {
        RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};
        Renderer2DImagesView::Get()->DrawImage(
            "DefaultSceneBackground", rid_background, dest_background);
        RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
        Color color = {1.0f, 0.0f, 0.0f, 255};
        Renderer2DSolidColorsView::Get()->FillRect(rid_box, rect, color);
        if (SDL_GetTicks() % 600 > 300)
            RendererText::Get()->DrawString(
                rid_text, "Press to start", {0.5f, 0.5f},
                {1.0f, 1.0f, 1.0f, 1.0f}, true);
    }
}
