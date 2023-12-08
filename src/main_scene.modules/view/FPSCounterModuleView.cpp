#include "FPSCounterModuleView.h"
#include "core.render.text/view/RendererText.h"
#include "main_scene.modules/model/FPSCounterModule.h"

namespace Narradia
{
    FPSCounterModuleView::FPSCounterModuleView() {

        rid_text = RendererText::Get()->NewString();
    }

    void FPSCounterModuleView::Render() {

        RendererText::Get()->DrawString(
            rid_text, "Fps: " + std::to_string(FPSCounterModule::Get()->fps()), {0.05f, 0.05f});
    }
}
