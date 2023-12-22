#include "model_display_module_view.h"
#include "core-render-models/view/command/draw_model.h"
namespace Narradia
{
   void ModelDisplayModuleView::Render() {
      DrawModel("Player2", SDL_GetTicks(), {3.0f, 0.0f, 0.0f});
      DrawModel("MobBoar", SDL_GetTicks(), {-3.0f, 1.0f, 0.0f}, 0.0f, 0.7f);
   }
}
