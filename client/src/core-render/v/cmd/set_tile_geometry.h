#pragma once
#include "../renderer_tiles_view.h"
#include <vector>
namespace Narradia
{
   auto SetTileGeometry(
       RenderID vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3, Point3F &normal00,
       Point3F &normal10, Point3F &normal11, Point3F &normal01) -> void;
}
