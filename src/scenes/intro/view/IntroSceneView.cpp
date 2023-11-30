#include "IntroSceneView.h"
#include "core.drawing/view/ImageDrawingView.h"

namespace Narradia {
    /**
     * Render operations.
     */
    void IntroSceneView::RenderDerived() {
        ImageDrawingView::Get()->DrawImage(
            "DefaultSceneBackground", {0.0f, 0.0f, 1.0f, 1.0f});
        ImageDrawingView::Get()->DrawImage(
            "NarradiaLogo", {0.3f, 0.1f, 0.4f, 0.2f});
    }
}
