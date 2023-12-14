#include "stop_models_batch_drawing.h"
namespace Narradia
{
   void StopModelsBatchDrawing() {
      auto renderer = RendererModelsView::get();
      renderer->set_is_batch_drawing(false);
   }
}
