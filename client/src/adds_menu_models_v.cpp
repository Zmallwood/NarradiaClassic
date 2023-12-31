#if 1
#include "adds-menu_models_v.h"
#include "rend_models_v.h"
#endif

namespace Narradia
{
   void MenuModelsAddV::Render() {
      DrawModel("Player2", SDL_GetTicks(), {3.0f, 0.0f, 0.0f});
      DrawModel("MobBoar", SDL_GetTicks(), {-3.0f, 1.0f, 0.0f}, 0.0f, 0.7f);
   }
}
