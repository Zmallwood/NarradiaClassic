#if 1
#include "main_pg-adds-visual_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "main_pg-adds-visual.h"
#endif

namespace Narradia
{
    // FPSCounterModuleV
#if 1
   FPSCounterAddV::FPSCounterAddV()
   {
      rid_text = NewString();
   }
   void FPSCounterAddV::Render()
   {
      DrawString(
          rid_text, "Fps: " + std::to_string(FPSCounterAdd::get()->fps()), {0.95f, 0.05f});
   }
#endif
}
