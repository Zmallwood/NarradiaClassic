#pragma once
#include "../../../common/system/typedefs.h"
#include "../../../conf/model/conf.h"
#include "../../../core.assets/model/image_bank.h"
#include "../../view/camera_gl.h"
#include "../../view/renderer_tiles_view.h"
#include "world.actors/model/player.h"
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
