#if 1
#include "stop_models_batch_drawing.h"
#include "rend-models/rend_models_v.h"
#endif

namespace Narradia
{
   auto StopModelsBatchDrawing() -> void {
      auto renderer = RendModelsV::get();
      renderer->set_is_batch_drawing(false);
   }
}
