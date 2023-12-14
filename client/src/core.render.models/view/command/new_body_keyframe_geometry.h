#pragma once
#include "../../../core.assets/model/image_bank.h"
#include "../../../core.render/view/camera_gl.h"
#include "../renderer_models_view.h"
namespace Narradia
{
   void NewBodyKeyframeGeometry(
       std::string_view image_name, float ms_time, GLuint vao_id, std::vector<Vertex3F> vertices,
       std::vector<Point3F> vertex_normals);
}
