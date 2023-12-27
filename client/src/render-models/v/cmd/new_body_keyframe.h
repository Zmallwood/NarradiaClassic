#pragma once

#include "render-models/v/renderer_models_view.h"

namespace Narradia
{
   auto NewBodyKeyframe(std::string_view model_name, float ms_time) -> RenderID;
}
