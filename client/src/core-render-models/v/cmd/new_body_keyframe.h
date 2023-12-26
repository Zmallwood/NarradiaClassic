#pragma once
#include "../renderer_models_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Creates a new keyframe for a body in a model at a speicic point in time and stores it
   /// in the internal data structure of the renderer. Returns RID of the created keyframe.
   ///
   /// @param[in] model_name Name of model to create the keyframe for.
   /// @param[in] ms_time Point in time in the animation to create the keyframe for.
   /// @return RID of the newly created keyframe.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewBodyKeyframe(std::string_view model_name, float ms_time) -> RenderID;
}
