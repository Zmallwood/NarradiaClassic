#if 1
#include "stop_tile_batch_drawing.h"
#include "render/renderer_tiles_v.h"
#endif

namespace Narradia
{
   auto StopTileBatchDrawing() -> void
   {
      auto renderer = RendererTilesV::get();
      renderer->set_is_batch_drawing(false);
      glUseProgram(0);
      glDisable(GL_CULL_FACE);
   }
}
