#if 1
#include "new_tile.h"
#include "render/renderer_tiles_v.h"
#endif

namespace Narradia
{
   RenderID NewTile()
   {
      auto num_vertices = 4;
      auto renderer = RendererTilesV::get();
      auto renderer_base = renderer->renderer_base();
      auto vertex_array_id = renderer_base->GenNewVAOId();
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vertex_array_id);
      auto position_buffer_id =
          renderer_base->GenNewBufId(BufferTypes::Positions3D, vertex_array_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vertex_array_id);
      auto uv_buffer_id = renderer_base->GenNewBufId(BufferTypes::Uvs, vertex_array_id);
      auto normal_buffer_id = renderer_base->GenNewBufId(BufferTypes::Normals, vertex_array_id);
      glBindVertexArray(vertex_array_id);
      renderer->SetIndicesData(index_buffer_id, num_vertices, nullptr);
      renderer->SetData(position_buffer_id, num_vertices, nullptr, BufferTypes::Positions3D);
      renderer->SetData(color_buffer_id, num_vertices, nullptr, BufferTypes::Colors);
      renderer->SetData(uv_buffer_id, num_vertices, nullptr, BufferTypes::Uvs);
      renderer->SetData(normal_buffer_id, num_vertices, nullptr, BufferTypes::Normals);
      glBindVertexArray(0);
      return vertex_array_id;
   }
}
