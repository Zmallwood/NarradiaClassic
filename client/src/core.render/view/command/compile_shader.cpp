#include "compile_shader.h"
namespace Narradia
{
   auto CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) -> GLuint {
      *shader = glCreateShader(shader_type);
      glShaderSource(*shader, 1, &shader_src, NULL);
      glCompileShader(*shader);
      GLint shader_compiled = GL_FALSE;
      glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);
      return shader_compiled;
   }
}
