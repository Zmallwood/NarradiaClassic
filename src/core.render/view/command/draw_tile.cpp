#include "draw_tile.h"
#include "draw_image_polygon.h"

namespace Narradia {
  void DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off) {
    DrawImagePolygon(image_name, vao_id, 4, depth_test_off);
  }
}
