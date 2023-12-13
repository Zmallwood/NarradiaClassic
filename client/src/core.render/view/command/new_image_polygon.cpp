#include "new_image_polygon.h"
#include "core.render/view/renderer_tiles_view.h"
namespace Narradia
{
    RenderID NewImagePolygon(int num_vertices) {
        auto renderer = RendererTilesView::get();
        auto renderer_base = renderer->renderer_base();
        auto vertex_array_id = renderer_base->GenerateNewVertexArrayId();
        auto index_buffer_id =
            renderer_base->GenerateNewBufferId(BufferTypes::Indices, vertex_array_id);
        auto position_buffer_id =
            renderer_base->GenerateNewBufferId(BufferTypes::Positions3D, vertex_array_id);
        auto color_buffer_id =
            renderer_base->GenerateNewBufferId(BufferTypes::Colors, vertex_array_id);
        auto uv_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Uvs, vertex_array_id);
        auto normal_buffer_id =
            renderer_base->GenerateNewBufferId(BufferTypes::Normals, vertex_array_id);
        renderer->UseVaoBegin(vertex_array_id);
        renderer->SetIndicesData(index_buffer_id, num_vertices, nullptr);
        renderer->SetData(position_buffer_id, num_vertices, nullptr, BufferTypes::Positions3D);
        renderer->SetData(color_buffer_id, num_vertices, nullptr, BufferTypes::Colors);
        renderer->SetData(uv_buffer_id, num_vertices, nullptr, BufferTypes::Uvs);
        renderer->SetData(normal_buffer_id, num_vertices, nullptr, BufferTypes::Normals);
        renderer->UseVaoEnd();
        return vertex_array_id;
    }
}
