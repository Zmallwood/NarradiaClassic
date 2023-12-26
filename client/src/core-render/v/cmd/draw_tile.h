#pragma once
#include "../../../conf/m/consts.h"
#include "../../../core-assets/m/image_bank.h"
#include "../../v/camera_gl.h"
#include "../../v/renderer_tiles_view.h"
#include "world-actors/m/player.h"
namespace Narradia
{
   auto DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off = false) -> void;
}
