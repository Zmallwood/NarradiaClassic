#if 1
#include "set_tile_geometry.h"
#include "render/renderer_tiles_v.h"
#endif

namespace Narradia
{
   auto SetTileGeometry(RenderID vao_id, Square<Vertex3F> &verts) -> void
   {
      std::vector<Vertex3F> vertices;
      vertices.push_back(verts._00);
      vertices.push_back(verts._10);
      vertices.push_back(verts._11);
      vertices.push_back(verts._01);
      auto renderer = RendererTilesV::get();
      auto renderer_base = renderer->renderer_base();
      if (!renderer->is_batch_drawing())
         renderer->UseVAOBegin(vao_id);
      std::vector<int> indices(vertices.size());
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;
      std::vector<float> uvs;
      std::vector<float> normals;
      for (auto &vertex : vertices)
      {
         positions.push_back(vertex.position.x);
         positions.push_back(vertex.position.y);
         positions.push_back(vertex.position.z);
         colors.push_back(vertex.color.r);
         colors.push_back(vertex.color.g);
         colors.push_back(vertex.color.b);
         colors.push_back(vertex.color.a);
         uvs.push_back(vertex.uv.x);
         uvs.push_back(vertex.uv.y);
         auto vertex_normal = vertex.normal;
         normals.push_back(vertex_normal.x);
         normals.push_back(vertex_normal.y);
         normals.push_back(vertex_normal.z);
      }
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions3D, vao_id);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base->BufId(BufferTypes::Uvs, vao_id);
      auto normal_buffer_id = renderer_base->BufId(BufferTypes::Normals, vao_id);
      glBindVertexArray(vao_id);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions3D,
          RendererTilesV::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, RendererTilesV::kLocationColor);
      renderer->UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, RendererTilesV::kLocationUv);
      renderer->UpdateData(
          normal_buffer_id, normals, BufferTypes::Normals, RendererTilesV::kLocationNormal);
      glBindVertexArray(0);
      if (!renderer->is_batch_drawing())
         renderer->UseVAOEnd();
   }
}
