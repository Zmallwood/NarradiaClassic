#pragma once
#include "../../../core-assets/m/model_bank.h"
#include "../renderer_models_view.h"
#include "new_body_keyframe.h"
#include "new_body_keyframe_geometry.h"
namespace Narradia
{
   auto NewModel(std::string_view model_name) -> void;
}
