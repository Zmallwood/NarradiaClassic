#include "SetImagePolygonGeometry.h"
#include "../RendererTilesView.h"

namespace Narradia
{
    void SetImagePolygonGeometry(RenderId vao_id, std::vector<Vertex3F> &vertices)
    {
        auto renderer = RendererTilesView::Get();
        auto renderer_base = renderer->renderer_base();

        if (!renderer->is_batch_drawing())
            renderer->UseVaoBegin(vao_id);

        std::vector<int> indices(vertices.size());
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;
        std::vector<float> normals;

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
            auto vertex_normal = vertex.normal;
            normals.push_back(vertex_normal.x);
            normals.push_back(vertex_normal.y);
            normals.push_back(vertex_normal.z);
        }

        auto index_buffer_id = renderer_base->GetBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id = renderer_base->GetBufferId(BufferTypes::Positions3D, vao_id);
        auto color_buffer_id = renderer_base->GetBufferId(BufferTypes::Colors, vao_id);
        auto uv_buffer_id = renderer_base->GetBufferId(BufferTypes::Uvs, vao_id);
        auto normal_buffer_id = renderer_base->GetBufferId(BufferTypes::Normals, vao_id);
        glBindVertexArray(vao_id);
        renderer->UpdateIndicesData(index_buffer_id, indices);
        renderer->UpdateData(
            position_buffer_id, positions, BufferTypes::Positions3D,
            RendererTilesView::kLocationPosition);
        renderer->UpdateData(
            color_buffer_id, colors, BufferTypes::Colors, RendererTilesView::kLocationColor);
        renderer->UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, RendererTilesView::kLocationUv);
        renderer->UpdateData(
            normal_buffer_id, normals, BufferTypes::Normals, RendererTilesView::kLocationNormal);
        glBindVertexArray(0);

        if (!renderer->is_batch_drawing())
            renderer->UseVaoEnd();
    }
}
