#include "fps_counter_module_view.h"
#include "core.render.text/view/renderer_text.h"
#include "core.render.text/view/command/draw_string.h"
#include "core.render.text/view/command/new_string.h"
#include "main_scene.modules/model/fps_counter_module.h"

namespace Narradia {
  FPSCounterModuleView::FPSCounterModuleView() {
    rid_text = NewString();
  }

  void FPSCounterModuleView::Render() {
    DrawString(rid_text, "Fps: " + std::to_string(FPSCounterModule::Get()->fps()), {0.05f, 0.05f});
  }
}
