#if 1
#include "model_display_add_v.h"
#include "render-models/cmd_v/draw_model.h"
#endif

namespace Narradia
{
   void ModelDisplayAddV::Render()
   {
      DrawModel("Player2", SDL_GetTicks(), {3.0f, 0.0f, 0.0f});
      DrawModel("MobBoar", SDL_GetTicks(), {-3.0f, 1.0f, 0.0f}, 0.0f, 0.7f);
   }
}
