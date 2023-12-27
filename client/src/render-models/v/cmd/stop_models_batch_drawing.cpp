#if 1
#include "stop_models_batch_drawing.h"
#include "render-models/v/renderer_models_view.h"
#endif

namespace Narradia
{
   auto StopModelsBatchDrawing() -> void
   {
      auto renderer = RendererModelsView::get();
      renderer->set_is_batch_drawing(false);
   }
}
