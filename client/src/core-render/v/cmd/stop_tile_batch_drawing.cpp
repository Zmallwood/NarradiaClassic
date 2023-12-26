#include "stop_tile_batch_drawing.h"
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
