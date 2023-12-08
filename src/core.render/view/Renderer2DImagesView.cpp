#include "Renderer2DImagesView.h"
#include "core.assets/model/ImageBank.h"
#include <GL/glew.h>

namespace Narradia {
    /**
     * Create the shader program for the provided shader sources.
     */
    Renderer2DImagesView::Renderer2DImagesView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/2DImagesVertex.glsl"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/2DImagesFragment.glsl"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
    }

    /**
     * Prepares resources for a new image later to be rendered, and returns an
     * id.
     */
    RenderId Renderer2DImagesView::NewImage() {
        auto vao_id = renderer_base_->GenerateNewVertexArrayId();
        UseVaoBegin(vao_id);
        auto index_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id =
            renderer_base_->GenerateNewBufferId(BufferTypes::Positions2D, vao_id);
        auto color_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Colors, vao_id);
        auto uv_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Uvs, vao_id);
        SetIndicesData(index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
        SetData(
            position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
            BufferTypes::Positions2D);
        SetData(
            color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
        SetData(uv_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Uvs);
        UseVaoEnd();
        return vao_id;
    }

    /**
     * Draws an image to the canvas, must previously have been initialized with
     * NewImage().
     */
    void Renderer2DImagesView::DrawImage(
        std::string_view image_name, RenderId rid, const RectF &dest, Color color) const {
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
        UseVaoBegin(rid);
        auto index_buffer_id = renderer_base_->GetBufferId(BufferTypes::Indices, rid);
        auto position_buffer_id = renderer_base_->GetBufferId(BufferTypes::Positions2D, rid);
        auto color_buffer_id = renderer_base_->GetBufferId(BufferTypes::Colors, rid);
        auto uv_buffer_id = renderer_base_->GetBufferId(BufferTypes::Uvs, rid);
        UpdateIndicesData(index_buffer_id, indices);
        UpdateData(position_buffer_id, positions, BufferTypes::Positions2D, kLocationPosition);
        UpdateData(color_buffer_id, colors, BufferTypes::Colors, kLocationColor);
        UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, kLocationUv);
        glDrawElements(
            GL_TRIANGLE_FAN, RendererBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
        UseVaoEnd();
    }

    /**
     * Forwarding cleanup command.
     */
    Renderer2DImagesView::~Renderer2DImagesView() {
        CleanupBase();
    }
}
