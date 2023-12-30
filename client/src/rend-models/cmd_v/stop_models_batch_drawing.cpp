#if 1
#include "stop_models_batch_drawing.h"
#include "rend-models/renderer_models_v.h"
#endif

namespace Narradia
{
   auto StopModelsBatchDrawing() -> void {
      auto renderer = RendererModelsV::get();
      renderer->set_is_batch_drawing(false);
   }
}
