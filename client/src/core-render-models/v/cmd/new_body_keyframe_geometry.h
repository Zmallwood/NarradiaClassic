#pragma once
#include "../../../core-render/v/camera_gl.h"
#include "../renderer_models_view.h"
namespace Narradia
{
   auto NewBodyKeyframeGeometry(
       GLuint vao_id, std::vector<Vertex3F> vertices, std::vector<Point3F> vertex_normals) -> void;
}
