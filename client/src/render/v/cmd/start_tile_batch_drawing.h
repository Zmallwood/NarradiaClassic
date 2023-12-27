#pragma once

#include "conf/m/consts.h"
#include "world-actors/m/player.h"
#include "render/v/camera_gl.h"
#include "render/v/renderer_tiles_view.h"
#include "world-struct/m/world.h"

namespace Narradia
{
   auto StartTileBatchDrawing() -> void;
}
