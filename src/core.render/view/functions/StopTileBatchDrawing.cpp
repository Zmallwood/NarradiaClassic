#include "StopTileBatchDrawing.h"
#include "../RendererTilesView.h"

namespace Narradia {
    void StopTileBatchDrawing() {
        auto renderer = RendererTilesView::Get();
        renderer->set_is_batch_drawing(false);
        glUseProgram(0);
        glDisable(GL_CULL_FACE);
    }
}
