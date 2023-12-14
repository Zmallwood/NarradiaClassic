#include "model_display_module_view.h"
#include "core.render.models/view/renderer_models_view.h"
namespace Narradia
{
   void ModelDisplayModuleView::Render() {
      RendererModelsView::get()->DrawModel("Player2", SDL_GetTicks(), {3.0f, 0.0f, 0.0f});
      RendererModelsView::get()->DrawModel("MobBoar", SDL_GetTicks(), {-3.0f, 1.0f, 0.0f}, 0.0f, 0.7f);
   }
}
