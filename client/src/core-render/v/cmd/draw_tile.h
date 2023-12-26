#pragma once
#include "../../../conf/m/consts.h"
#include "../../../core-assets/m/image_bank.h"
#include "../../v/camera_gl.h"
#include "../../v/renderer_tiles_view.h"
#include "world-actors/m/player.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders a tile in 3D space.
   ///
   /// @param[in] image_name Image name.
   /// @param[in] vao_id VAO ID previously obtained from NewTile().
   /// @param[in] depth_test_off Enable/disable depth test during rendering.
   ////////////////////////////////////////////////////////////////////////////////
   auto DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off = false) -> void;
}
