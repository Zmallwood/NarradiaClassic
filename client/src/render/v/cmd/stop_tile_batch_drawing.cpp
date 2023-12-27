#if 1
#include "stop_tile_batch_drawing.h"
#include "render/v/renderer_tiles_view.h"
#endif

namespace Narradia
{
   auto StopTileBatchDrawing() -> void
   {
      auto renderer = RendererTilesView::get();
      renderer->set_is_batch_drawing(false);
      glUseProgram(0);
      glDisable(GL_CULL_FACE);
   }
}
