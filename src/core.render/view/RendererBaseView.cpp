#include "RendererBaseView.h"
#include "../model/ShaderProgram.h"
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

    void RendererBaseView::SetData(
        GLuint vbo_id, int num_vertices, const void *data,
        BufferTypes buffer_type, int layout_location) const {
        SetArrayBufferData(
            vbo_id, num_vertices, data,
            RendererBase::kNumFloatsPerEntry.at(buffer_type), layout_location);
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

    void RendererBaseView::UpdateData(
        GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
        int layout_location) {
        UpdateArrayBufferData(
            vbo_id, data, RendererBase::kNumFloatsPerEntry.at(buffer_type),
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
