#pragma once

typedef char GLchar;

namespace Narradia
{
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
}
