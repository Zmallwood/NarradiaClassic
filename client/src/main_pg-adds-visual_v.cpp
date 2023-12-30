#if 1
#include "main_pg-adds-visual_v.h"
#include "main_pg-adds-visual.h"
#include "rend-text/renderer_text.h"
#endif

namespace Narradia
{
   // FPSCounterModuleV
#if 1
   FPSCounterAddV::FPSCounterAddV() {
      rid_text = NewString();
   }
   void FPSCounterAddV::Render() {
      DrawString(rid_text, "Fps: " + std::to_string(FPSCounterAdd::get()->fps()), {0.95f, 0.05f});
   }
#endif
}
