#if 1
#include "main_scene-adds-visible_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "main_scene-adds-visible.h"
#endif

namespace Narradia
{
    // FPSCounterModuleV
#if 1
   FPSCounterModuleV::FPSCounterModuleV()
   {
      rid_text = NewString();
   }
   void FPSCounterModuleV::Render()
   {
      DrawString(
          rid_text, "Fps: " + std::to_string(FPSCounterModule::get()->fps()), {0.95f, 0.05f});
   }
#endif
}
