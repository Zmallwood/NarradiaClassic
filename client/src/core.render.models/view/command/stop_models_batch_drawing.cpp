#include "stop_models_batch_drawing.h"
namespace Narradia
{
   auto StopModelsBatchDrawing() -> void {
      auto renderer = RendererModelsView::get();
      renderer->set_is_batch_drawing(false);
   }
}
