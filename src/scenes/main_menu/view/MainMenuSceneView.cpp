#include "MainMenuSceneView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"

namespace Narradia {
    MainMenuSceneView::MainMenuSceneView() {
        rid_box = Renderer2DSolidColorsView::Get()->NewRect();
    }

    /**
     * Render operations.
     */
    void MainMenuSceneView::RenderDerived() {
        RectF rect = {0.15f, 0.15f, 0.2f, 0.1f};
        Color color = {0, 0, 255, 255};
        Renderer2DSolidColorsView::Get()->FillRect(rid_box, rect, color);
    }
}
