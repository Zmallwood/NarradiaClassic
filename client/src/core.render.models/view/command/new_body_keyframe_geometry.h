#pragma once
#include "../../../core.render/view/camera_gl.h"
#include "../renderer_models_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Create GL buffers into which a keyframe body is loaded.
   ///
   /// @param[[TODO:direction]] vao_id VAO ID of the 3D model to which the body belongs.
   /// @param[[TODO:direction]] vertices Vertices data.
   /// @param[[TODO:direction]] vertex_normals Vertex normals data.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewBodyKeyframeGeometry(
       GLuint vao_id, std::vector<Vertex3F> vertices, std::vector<Point3F> vertex_normals) -> void;
}
