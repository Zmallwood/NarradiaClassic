#include "new_body_keyframe_geometry.h"
namespace Narradia
{
   void NewBodyKeyframeGeometry(
       std::string_view image_name, float ms_time, GLuint vao_id, std::vector<Vertex3F> vertices,
       std::vector<Point3F> vertex_normals) {
      auto renderer = RendererModelsView::get();
      auto renderer_base = renderer->renderer_base();
      glEnable(GL_DEPTH_TEST);
      renderer->UseVAOBegin(vao_id);
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE,
          value_ptr(CameraGL::get()->perspective_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, value_ptr(CameraGL::get()->view_matrix()));
      glUniform1f(renderer->location_alpha(), 1.0f);
      auto image_id = ImageBank::get()->GetImage(image_name);
      glBindTexture(GL_TEXTURE_2D, image_id);
      std::vector<int> indices(vertices.size());
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;
      std::vector<float> uvs;
      std::vector<float> normals;
      auto i = 0;
      for (auto &vertex : vertices) {
         positions.push_back(vertex.position.x);
         positions.push_back(vertex.position.y);
         positions.push_back(vertex.position.z);
         colors.push_back(vertex.color.r);
         colors.push_back(vertex.color.g);
         colors.push_back(vertex.color.b);
         colors.push_back(vertex.color.a);
         uvs.push_back(vertex.uv.x);
         uvs.push_back(vertex.uv.y);
         if (vertex_normals.size() > i) {
            auto vertex_normal = vertex_normals.at(i);
            normals.push_back(vertex_normal.x);
            normals.push_back(-vertex_normal.y);
            normals.push_back(vertex_normal.z);
         }
         i++;
      }
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->GenNewBufId(BufferTypes::Positions3D, vao_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base->GenNewBufId(BufferTypes::Uvs, vao_id);
      auto normal_buffer_id = renderer_base->GenNewBufId(BufferTypes::Normals, vao_id);
      auto num_vertices = vertices.size();
      renderer->SetIndicesData(index_buffer_id, num_vertices, indices.data());
      renderer->SetData(
          position_buffer_id, num_vertices, positions.data(), BufferTypes::Positions3D,
          RendererModelsView::kLocationPosition);
      renderer->SetData(
          color_buffer_id, num_vertices, colors.data(), BufferTypes::Colors,
          RendererModelsView::kLocationColor);
      renderer->SetData(
          uv_buffer_id, num_vertices, uvs.data(), BufferTypes::Uvs,
          RendererModelsView::kLocationUv);
      renderer->SetData(
          normal_buffer_id, num_vertices, normals.data(), BufferTypes::Normals,
          RendererModelsView::kLocationNormal);
      renderer->UseVAOEnd();
   }
}
