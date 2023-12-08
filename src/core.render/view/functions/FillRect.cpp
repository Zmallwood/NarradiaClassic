#include "FillRect.h"
#include "../Renderer2DSolidColorsView.h"

namespace Narradia {

    /**
     * Renders a color-filled rectangle to the canvas, must previously have been
     * initialized with NewRect().
     */
    void FillRect(RenderId vao_id, RectF rect, Color color) {

        auto renderer = Renderer2DSolidColorsView::Get();
        auto renderer_base = renderer->renderer_base();
        auto gl_rect = rect.ToGLRectF();
        Vertex2F vertices[RendererBase::kNumVerticesInRectangle];
        vertices[0].position = {gl_rect.x, gl_rect.y - gl_rect.height};
        vertices[1].position = {gl_rect.x, gl_rect.y};
        vertices[2].position = {gl_rect.x + gl_rect.width, gl_rect.y};
        vertices[3].position = {gl_rect.x + gl_rect.width, gl_rect.y - gl_rect.height};
        glDisable(GL_DEPTH_TEST);
        std::vector<int> indices(RendererBase::kNumVerticesInRectangle);
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;

        for (auto &vertex : vertices) {
            positions.push_back(vertex.position.x);
            positions.push_back(vertex.position.y);
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
        }

        renderer->UseVaoBegin(vao_id);
        auto index_buffer_id = renderer_base->GetBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id = renderer_base->GetBufferId(BufferTypes::Positions2D, vao_id);
        auto color_buffer_id = renderer_base->GetBufferId(BufferTypes::Colors, vao_id);
        renderer->UpdateIndicesData(index_buffer_id, indices);
        renderer->UpdateData(
            position_buffer_id, positions, BufferTypes::Positions2D,
            Renderer2DSolidColorsView::kLocationPosition);
        renderer->UpdateData(
            color_buffer_id, colors, BufferTypes::Colors,
            Renderer2DSolidColorsView::kLocationColor);
        glDrawElements(
            GL_TRIANGLE_FAN, RendererBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
        renderer->UseVaoEnd();
    }
}
