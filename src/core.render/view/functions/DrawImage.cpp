#include "DrawImage.h"
#include "../Renderer2DImagesView.h"
#include "core.assets/model/ImageBank.h"

namespace Narradia {

    /**
     * Draws an image to the canvas, must previously have been initialized with
     * NewImage().
     */
    void DrawImage(std::string_view image_name, RenderId rid, const RectF &dest, Color color) {

        auto renderer = Renderer2DImagesView::Get();
        auto renderer_base = renderer->renderer_base();
        auto gl_rect = dest.ToGLRectF();
        Vertex2F vertices[RendererBase::kNumVerticesInRectangle];
        vertices[0].position = {gl_rect.x, gl_rect.y - gl_rect.height};
        vertices[1].position = {gl_rect.x, gl_rect.y};
        vertices[2].position = {gl_rect.x + gl_rect.width, gl_rect.y};
        vertices[3].position = {gl_rect.x + gl_rect.width, gl_rect.y - gl_rect.height};
        vertices[0].uv = {0.0f, 1.0f};
        vertices[1].uv = {0.0f, 0.0f};
        vertices[2].uv = {1.0f, 0.0f};
        vertices[3].uv = {1.0f, 1.0f};
        glDisable(GL_DEPTH_TEST);
        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        std::vector<int> indices(RendererBase::kNumVerticesInRectangle);
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;

        for (auto &vertex : vertices) {
            positions.push_back(vertex.position.x);
            positions.push_back(vertex.position.y);
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
            uvs.push_back(vertex.uv.x);
            uvs.push_back(vertex.uv.y);
        }

        renderer->UseVaoBegin(rid);
        auto index_buffer_id = renderer_base->GetBufferId(BufferTypes::Indices, rid);
        auto position_buffer_id = renderer_base->GetBufferId(BufferTypes::Positions2D, rid);
        auto color_buffer_id = renderer_base->GetBufferId(BufferTypes::Colors, rid);
        auto uv_buffer_id = renderer_base->GetBufferId(BufferTypes::Uvs, rid);
        renderer->UpdateIndicesData(index_buffer_id, indices);
        renderer->UpdateData(
            position_buffer_id, positions, BufferTypes::Positions2D,
            Renderer2DImagesView::kLocationPosition);
        renderer->UpdateData(
            color_buffer_id, colors, BufferTypes::Colors, Renderer2DImagesView::kLocationColor);
        renderer->UpdateData(
            uv_buffer_id, uvs, BufferTypes::Uvs, Renderer2DImagesView::kLocationUv);
        glDrawElements(
            GL_TRIANGLE_FAN, RendererBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
        renderer->UseVaoEnd();
    }
}
