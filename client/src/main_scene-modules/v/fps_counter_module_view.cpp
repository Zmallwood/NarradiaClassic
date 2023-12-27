#include "fps_counter_module_view.h"
#include "render-text/v/cmd/draw_string.h"
#include "render-text/v/cmd/new_string.h"
#include "main_scene-modules/m/fps_counter_module.h"

namespace Narradia
{
   FPSCounterModuleView::FPSCounterModuleView()
   {
      rid_text = NewString();
   }

   void FPSCounterModuleView::Render()
   {
      DrawString(
          rid_text, "Fps: " + std::to_string(FPSCounterModule::get()->fps()), {0.95f, 0.05f});
   }
}
