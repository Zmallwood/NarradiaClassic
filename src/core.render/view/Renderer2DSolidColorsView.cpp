#include "Renderer2DSolidColorsView.h"
#include <GL/glew.h>

namespace Narradia {
    /**
     * Create the shader program from shader sources.
     */
    Renderer2DSolidColorsView::Renderer2DSolidColorsView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model//2DSolidColorsVertex.glsl"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/2DSolidColorsFragment.glsl"
            ;
        GetShaderProgramView()->Create(
            vertex_shader_source, fragment_shader_source);
    }

    /**
     * Prepares resources for a new colored rectangle, later to be rendered,
     * returning an id.
     */
    RenderId Renderer2DSolidColorsView::NewRect() {
        auto vao_id = renderer_base_->GenerateNewVertexArrayId();
        UseVaoBegin(vao_id);
        auto index_buffer_id =
            renderer_base_->GenerateNewBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Positions2D, vao_id);
        auto color_buffer_id =
            renderer_base_->GenerateNewBufferId(BufferTypes::Colors, vao_id);
        SetIndicesData(
            index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
        SetData(
            position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
            BufferTypes::Positions2D);
        SetData(
            color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
            BufferTypes::Colors);
        UseVaoEnd();

        return vao_id;
    }

    /**
     * Renders a color-filled rectangle to the canvas, must previously have been
     * initialized with NewRect().
     */
    void Renderer2DSolidColorsView::FillRect(
        RenderId vao_id, RectF rect, Color color) {
        auto gl_rect = rect.ToGLRectF();
        Vertex2F vertices[RendererBase::kNumVerticesInRectangle];
        vertices[0].position = {gl_rect.x, gl_rect.y - gl_rect.height};
        vertices[1].position = {gl_rect.x, gl_rect.y};
        vertices[2].position = {gl_rect.x + gl_rect.width, gl_rect.y};
        vertices[3].position = {
            gl_rect.x + gl_rect.width, gl_rect.y - gl_rect.height};
        vertices[0].color = color;
        vertices[1].color = color;
        vertices[2].color = color;
        vertices[3].color = color;
        glDisable(GL_DEPTH_TEST);
        std::vector<int> indices(RendererBase::kNumVerticesInRectangle);
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        for (auto &vertex : vertices) {
            positions.push_back(vertex.position.x);
            positions.push_back(vertex.position.y);
            colors.push_back(vertex.color.r);
            colors.push_back(vertex.color.g);
            colors.push_back(vertex.color.b);
            colors.push_back(vertex.color.a);
        }
        UseVaoBegin(vao_id);
        auto index_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Positions2D, vao_id);
        auto color_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Colors, vao_id);
        UpdateIndicesData(index_buffer_id, indices);
        UpdateData(
            position_buffer_id, positions, BufferTypes::Positions2D,
            kLocationPosition);
        UpdateData(
            color_buffer_id, colors, BufferTypes::Colors, kLocationColor);
        glDrawElements(
            GL_TRIANGLE_FAN, RendererBase::kNumVerticesInRectangle,
            GL_UNSIGNED_INT, NULL);
        UseVaoEnd();
    }

    /**
     * Forwarding cleanup command.
     */
    Renderer2DSolidColorsView::~Renderer2DSolidColorsView() {
        CleanupBase();
    }
}
