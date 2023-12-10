#include "update_draw_tile.h"
#include "draw_image_polygon.h"
#include "set_image_polygon_geometry.h"
namespace Narradia {
  void UpdateDrawTile(
      std::string_view image_name, RenderID vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
      Vertex3F &v3, Point3F &normal00, Point3F &normal10, Point3F &normal11, Point3F &normal01,
      bool depth_test_off) {
    std::vector<Vertex3F> vertices;
    v0.normal = normal00;
    v1.normal = normal10;
    v2.normal = normal11;
    v3.normal = normal01;
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    SetImagePolygonGeometry(vao_id, vertices);
    DrawImagePolygon(image_name, vao_id, 4, depth_test_off);
  }
}
