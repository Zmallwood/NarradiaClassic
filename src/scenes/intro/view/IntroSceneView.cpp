#include "IntroSceneView.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"

namespace Narradia {
    IntroSceneView::IntroSceneView() {
        rid_box = Renderer2DSolidColorsView::Get()->NewRect();
        rid_background = Renderer2DImagesView::Get()->NewImage();
    }

    /**
     * Render operations.
     */
    void IntroSceneView::RenderDerived() {
        RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};
        Renderer2DImagesView::Get()->DrawImage(
            "DefaultSceneBackground", rid_background, dest_background);
        RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
        Color color = {255, 0, 0, 255};
        Renderer2DSolidColorsView::Get()->FillRect(rid_box, rect, color);
    }
}
