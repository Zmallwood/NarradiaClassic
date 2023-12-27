#pragma once

#include "conf/m/consts.h"
#include "assets/m/image_bank.h"
#include "render/v/camera_gl.h"
#include "render/v/renderer_tiles_view.h"
#include "world-actors/m/player.h"

namespace Narradia
{
   auto DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off = false) -> void;
}
