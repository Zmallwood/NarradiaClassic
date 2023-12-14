#pragma once
#include "../../../core.assets/model/model_bank.h"
#include "../renderer_models_view.h"
#include "new_body_keyframe.h"
#include "new_body_keyframe_geometry.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for and initializes a new 3D model.
   ///
   /// @param[in] model_name Name of model to initialize.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewModel(std::string_view model_name) -> void;
}
