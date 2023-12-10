#include "stop_tile_batch_drawing.h"
#include "core.render/view/renderer_tiles_view.h"
namespace Narradia {
  void StopTileBatchDrawing() {
    auto renderer = RendererTilesView::Get();
    renderer->set_is_batch_drawing(false);
    glUseProgram(0);
    glDisable(GL_CULL_FACE);
  }
}
