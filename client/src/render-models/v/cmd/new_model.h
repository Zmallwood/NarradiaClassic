#pragma once

#include "assets/m/model_bank.h"
#include "render-models/v/renderer_models_view.h"
#include "new_body_keyframe.h"
#include "new_body_keyframe_geometry.h"

namespace Narradia
{
   auto NewModel(std::string_view model_name) -> void;
}
