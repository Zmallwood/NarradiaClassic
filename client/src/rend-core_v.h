#pragma once

#include "rend-core.h"

namespace Narradia
{
   class RendBase;
   class ShaderProgramV;

   class RendBaseV {
     public:
      RendBaseV();
      void UseVAOBegin(GLuint vao_id) const;
      void UseVAOEnd() const;
      void SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const;
      void SetData(
          GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
          int layout_location = -1) const;
      void UpdateIndicesData(GLuint indices_vbo_id, std::vector<int> &indices) const;
      void UpdateData(
          GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
          int layout_location) const;
      auto shader_program_view() {
         return shader_program_view_;
      }
      auto renderer_base() {
         return renderer_base_;
      }

     protected:
      GLuint GetUniformLocation(std::string_view var_name);
      void CleanupBase();

      std::shared_ptr<RendBase> renderer_base_;

     private:
      void SetArrayBufferData(
          GLuint vbo_id, int num_vertices, const void *data, int num_floats_per_entry,
          int layout_location = -1) const;
      void UpdateArrayBufferData(
          GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
          int layout_location) const;

      std::shared_ptr<ShaderProgramV> shader_program_view_;
   };

   // Belonging ShaderProgramV class
#if 1
   class ShaderProgram;

   class ShaderProgramV {
     public:
      ShaderProgramV();
      bool Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src);
      auto shader_program() {
         return shader_program_;
      }

     private:
      auto CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) -> GLuint;

      std::shared_ptr<ShaderProgram> shader_program_;
   };
#endif
}
