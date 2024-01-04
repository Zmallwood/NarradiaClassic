#include "rend-core.h"

namespace Narradia
{
// Model
#if 1
   // RendBase
#if 1
   GLuint RendBase::GenNewVAOId() {

      GLuint new_vao_id;
      glGenVertexArrays(1, &new_vao_id);
      vao_ids_.push_back(new_vao_id);

      return new_vao_id;
   }

   GLuint RendBase::GenNewBufId(BufferTypes buffer_type, GLuint vao_id) {

      GLuint new_buffer_id;
      glGenBuffers(1, &new_buffer_id);
      vbo_ids_[buffer_type][vao_id] = new_buffer_id;

      return new_buffer_id;
   }

   GLuint RendBase::BufId(BufferTypes buffer_type, GLuint vao_id) const {

      return vbo_ids_.at(buffer_type).at(vao_id);
   }

   void RendBase::CleanupBase() const {

      for (auto &buffer_type : vbo_ids_)
         for (auto &buffer_entry : buffer_type.second)
            glDeleteBuffers(1, &buffer_entry.second);

      for (auto vao_id : vao_ids_)
         glDeleteVertexArrays(1, &vao_id);
   }
#endif

   // ShaderProgram
#if 1
   void ShaderProgram::Cleanup() {

      glDeleteProgram(program_id_);
   }
#endif
#endif

// View
#if 1
   // RendBaseV
#if 1
   RendBaseV::RendBaseV()
       : shader_program_view_(std::make_shared<ShaderProgramV>()),
         renderer_base_(std::make_shared<RendBase>()) {
   }

   void RendBaseV::SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const {

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);

      glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          num_vertices * RendBase::kNumFloatsPerEntry.at(BufferTypes::Indices) * sizeof(float),
          data, GL_DYNAMIC_DRAW);
   }

   void RendBaseV::SetData(
       GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
       int layout_location) const {

      SetArrayBufferData(
          vbo_id, num_vertices, data, RendBase::kNumFloatsPerEntry.at(buffer_type),
          layout_location);
   }

   void RendBaseV::SetArrayBufferData(
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

   void RendBaseV::UpdateIndicesData(GLuint indices_vbo_id, std::vector<int> &indices) const {

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);

      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(), indices.data());
   }

   void RendBaseV::UpdateArrayBufferData(
       GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
       int layout_location) const {

      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(), data.data());

      glVertexAttribPointer(
          layout_location, num_floats_per_entry, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);

      glEnableVertexAttribArray(layout_location);
   }

   void RendBaseV::UpdateData(
       GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
       int layout_location) const {

      UpdateArrayBufferData(
          vbo_id, data, RendBase::kNumFloatsPerEntry.at(buffer_type), layout_location);
   }

   void RendBaseV::UseVAOBegin(GLuint vao_id) const {

      glUseProgram(shader_program_view_->shader_program()->program_id());
      glBindVertexArray(vao_id);
   }

   void RendBaseV::UseVAOEnd() const {

      glBindVertexArray(0);
      glUseProgram(0);
   }

   GLuint RendBaseV::GetUniformLocation(std::string_view var_name) {

      return glGetUniformLocation(
          shader_program_view_->shader_program()->program_id(), var_name.data());
   }

   void RendBaseV::CleanupBase() {

      shader_program_view_->shader_program()->Cleanup();
      renderer_base_->CleanupBase();
   }
#endif

   // ShaderProgramV
#if 1
   ShaderProgramV::ShaderProgramV()
       : shader_program_(std::make_shared<ShaderProgram>()) {
   }

   bool ShaderProgramV::Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src) {

      GLuint vertex_shader = 0;
      GLuint fragment_shader = 0;
      shader_program_->set_program_id(glCreateProgram());
      auto vertex_shader_res = CompileShader(vert_shader_src, &vertex_shader, GL_VERTEX_SHADER);
      auto success = true;

      if (vertex_shader_res != GL_TRUE) {

         SDL_ShowSimpleMessageBox(
             SDL_MESSAGEBOX_ERROR, "Shader error", "Unable to compile vertex shader.", nullptr);

         printf("Unable to compile vertex shader %d!\n", vertex_shader);

         success = false;
      }
      if (success) {

         glAttachShader(shader_program_->program_id(), vertex_shader);
         auto fragment_shader_res =
             CompileShader(frag_shader_src, &fragment_shader, GL_FRAGMENT_SHADER);

         if (fragment_shader_res != GL_TRUE) {

            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR, "Shader error", "Unable to compile fragment shader.",
                nullptr);

            printf("Unable to compile fragment shader %d!\n", fragment_shader);

            success = false;
         }
      }
      if (success) {

         glAttachShader(shader_program_->program_id(), fragment_shader);
         glLinkProgram(shader_program_->program_id());

         GLint program_success = GL_TRUE;
         glGetProgramiv(shader_program_->program_id(), GL_LINK_STATUS, &program_success);

         if (program_success != GL_TRUE) {

            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR, "Shader error", "Error linking shader program.", nullptr);

            printf("Error linking program %d!\n", shader_program_->program_id());

            success = false;
         }
      }
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);

      return success;
   }

   GLuint
   ShaderProgramV::CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) {

      *shader = glCreateShader(shader_type);

      glShaderSource(*shader, 1, &shader_src, NULL);
      glCompileShader(*shader);

      GLint shader_compiled = GL_FALSE;
      glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);

      return shader_compiled;
   }
#endif
#endif
}
