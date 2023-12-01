#include "RendererBaseView.h"
#include "../model/ShaderProgram.h"
#include "core.render/model/BufferTypes.h"
#include "core.render/model/RendererBase.h"
#include "core.render/view/ShaderProgramView.h"

namespace Narradia {
    RendererBaseView::RendererBaseView()
        : shader_program_view_(std::make_shared<ShaderProgramView>()),
          renderer_base_(std::make_shared<RendererBase>()) {
    }

    void RendererBaseView::SetIndicesData(
        GLuint indices_vbo_id, int num_vertices, const void *data) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            num_vertices *
                RendererBase::kNumFloatsPerEntry.at(BufferTypes::Indices) *
                sizeof(float),
            data, GL_DYNAMIC_DRAW);
    }
    void RendererBaseView::SetArrayBufferData(
        GLuint vbo_id, int num_vertices, const void *data,
        int num_floats_per_entry, int layout_location) const {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        glBufferData(
            GL_ARRAY_BUFFER,
            num_vertices * num_floats_per_entry * sizeof(float), data,
            GL_DYNAMIC_DRAW);
        if (layout_location >= 0) {
            glVertexAttribPointer(
                layout_location, num_floats_per_entry, GL_FLOAT, GL_FALSE, 0,
                (const GLvoid *)0);
            glEnableVertexAttribArray(layout_location);
        }
    }

    void RendererBaseView::SetPositions2DData(
        GLuint pos_2d_vbo_id, int num_vertices, const void *data,
        int layout_location) const {
        SetArrayBufferData(
            pos_2d_vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Positions2D),
            layout_location);
    }

    void RendererBaseView::SetPositions3DData(
        GLuint pos_3d_vbo_id, int num_vertices, const void *data,
        int layout_location) const {
        SetArrayBufferData(
            pos_3d_vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Positions3D),
            layout_location);
    }

    void RendererBaseView::SetUvsData(
        GLuint uv_vbo_id, int num_vertices, const void *data,
        int layout_location) const {
        SetArrayBufferData(
            uv_vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Uvs),
            layout_location);
    }

    void RendererBaseView::SetColorsData(
        GLuint color_vbo_id, int num_vertices, const void *data,
        int layout_location) const {
        SetArrayBufferData(
            color_vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Colors),
            layout_location);
    }

    void RendererBaseView::SetNormalsData(
        GLuint normal_vbo_id, int num_vertices, const void *data,
        int layout_location) const {
        SetArrayBufferData(
            normal_vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Normals),
            layout_location);
    }

    void RendererBaseView::UpdateIndicesData(
        GLuint indices_vbo_id, std::vector<int> &indices) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(),
            indices.data());
    }

    void RendererBaseView::UpdateArrayBufferData(
        GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
        int layout_location) const {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        glBufferSubData(
            GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(), data.data());
        glVertexAttribPointer(
            layout_location, num_floats_per_entry, GL_FLOAT, GL_FALSE, 0,
            (const GLvoid *)0);
        glEnableVertexAttribArray(layout_location);
    }

    void RendererBaseView::UpdatePositions2DData(
        GLuint positions_vbo_id, std::vector<float> &positions,
        int layout_location) const {
        UpdateArrayBufferData(
            positions_vbo_id, positions,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Positions2D),
            layout_location);
    }

    void RendererBaseView::UpdatePositions3DData(
        GLuint positions_vbo_id, std::vector<float> &positions,
        int layout_location) const {
        UpdateArrayBufferData(
            positions_vbo_id, positions,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Positions3D),
            layout_location);
    }

    void RendererBaseView::UpdateUvsData(
        GLuint uvs_vbo_id, std::vector<float> &uvs, int layout_location) const {
        UpdateArrayBufferData(
            uvs_vbo_id, uvs,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Uvs),
            layout_location);
    }

    void RendererBaseView::UpdateColorsData(
        GLuint colors_vbo_id, std::vector<float> &colors,
        int layout_location) const {
        UpdateArrayBufferData(
            colors_vbo_id, colors,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Colors),
            layout_location);
    }

    void RendererBaseView::UpdateNormalsData(
        GLuint normals_vbo_id, std::vector<float> &normals,
        int layout_location) const {
        UpdateArrayBufferData(
            normals_vbo_id, normals,
            RendererBase::kNumFloatsPerEntry.at(BufferTypes::Normals),
            layout_location);
    }

    void RendererBaseView::UseVaoBegin(int vao_id) const {
        glUseProgram(shader_program_view_->shader_program()->program_id());
        glBindVertexArray(vao_id);
    }

    void RendererBaseView::UseVaoEnd() const {
        glBindVertexArray(0);
        glUseProgram(0);
    }

    GLuint RendererBaseView::GetUniformLocation(std::string_view var_name) {
        return glGetUniformLocation(
            shader_program_view_->shader_program()->program_id(),
            var_name.data());
    }

    std::shared_ptr<ShaderProgramView>
    RendererBaseView::GetShaderProgramView() const {
        return shader_program_view_;
    }

    void RendererBaseView::CleanupBase() {
        shader_program_view_->shader_program()->Cleanup();
    }
}
