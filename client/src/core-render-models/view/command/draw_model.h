#pragma once
#include "../../../conf/model/constants.h"
#include "../../../core-assets/model/image_bank.h"
#include "../../../core-assets/model/model_bank.h"
#include "../../../core-render/view/camera_gl.h"
#include "../renderer_models_view.h"
#include "world-actors/model/player.h"
#include <glm/glm.hpp>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders a 3D model to the 3D space.
   ///
   /// @param[in] model_name Name of model to render.
   /// @param[in] ms_time Point in time in animation.
   /// @param[in] position Position to render at.
   /// @param[in] rotation Rotation of rendered model in degrees.
   /// @param[in] scaling Scaling of rendererd model.
   /// @param[in] brightness Brightness of rendered model.
   /// @param[in] color_mod Color mulitplier.
   /// @param[in] no_fog Disabling of fog.
   /// @param[in] no_lighting Disabling of lighting.
   ////////////////////////////////////////////////////////////////////////////////
   auto DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation = 0.0f,
       float scaling = 1.0f, float brightness = 1.0f, glm::vec3 color_mod = {1.0f, 1.0f, 1.0f},
       bool no_fog = false, bool no_lighting = false) -> void;
}
