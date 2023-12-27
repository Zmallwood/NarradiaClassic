#pragma once

namespace Narradia
{
   auto NewBodyKeyframeGeometry(
       GLuint vao_id, std::vector<Vertex3F> vertices, std::vector<Point3F> vertex_normals) -> void;
}
