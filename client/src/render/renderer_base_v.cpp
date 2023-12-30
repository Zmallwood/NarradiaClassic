#if 1
#include "renderer_base_v.h"
#include "render/shader_program.h"
#include "shader_program_v.h"
#endif

namespace Narradia
{
   RendererBaseV::RendererBaseV()
       : shader_program_view_(std::make_shared<ShaderProgramV>()),
         renderer_base_(std::make_shared<RendererBase>()) {
   }
   void
   RendererBaseV::SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
      glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          num_vertices * RendererBase::kNumFloatsPerEntry.at(BufferTypes::Indices) * sizeof(float),
          data, GL_DYNAMIC_DRAW);
   }
   void RendererBaseV::SetData(
       GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
       int layout_location) const {
      SetArrayBufferData(
          vbo_id, num_vertices, data, RendererBase::kNumFloatsPerEntry.at(buffer_type),
          layout_location);
   }
   void RendererBaseV::SetArrayBufferData(
       GLuint vbo_id, int num_vertices, const void *data, int num_floats_per_entry,
       int layout_location) const {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glBufferData(
          GL_ARRAY_BUFFER, num_vertices * num_floats_per_entry * sizeof(float), data,
          GL_DYNAMIC_DRAW);
      if (layout_location >= 0) {
         glVertexAttribPointer(
             layout_location, num_floats_per_entry, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
         glEnableVertexAttribArray(layout_location);
      }
   }
   void RendererBaseV::UpdateIndicesData(GLuint indices_vbo_id, std::vector<int> &indices) const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(), indices.data());
   }
   void RendererBaseV::UpdateArrayBufferData(
       GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
       int layout_location) const {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(), data.data());
      glVertexAttribPointer(
          layout_location, num_floats_per_entry, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
      glEnableVertexAttribArray(layout_location);
   }
   void RendererBaseV::UpdateData(
       GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
       int layout_location) const {
      UpdateArrayBufferData(
          vbo_id, data, RendererBase::kNumFloatsPerEntry.at(buffer_type), layout_location);
   }
   void RendererBaseV::UseVAOBegin(GLuint vao_id) const {
      glUseProgram(shader_program_view_->shader_program()->program_id());
      glBindVertexArray(vao_id);
   }
   void RendererBaseV::UseVAOEnd() const {
      glBindVertexArray(0);
      glUseProgram(0);
   }
   GLuint RendererBaseV::GetUniformLocation(std::string_view var_name) {
      return glGetUniformLocation(
          shader_program_view_->shader_program()->program_id(), var_name.data());
   }
   void RendererBaseV::CleanupBase() {
      shader_program_view_->shader_program()->Cleanup();
      renderer_base_->CleanupBase();
   }
}
