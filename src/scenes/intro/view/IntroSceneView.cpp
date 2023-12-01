#include "IntroSceneView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"

namespace Narradia {
    IntroSceneView::IntroSceneView() {
        rid_box = Renderer2DSolidColorsView::Get()->NewRect();
    }

    /**
     * Render operations.
     */
    void IntroSceneView::RenderDerived() {
        RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
        Color color = {255, 0, 0, 255};
        Renderer2DSolidColorsView::Get()->FillRect(rid_box, rect, color);
    }
}
