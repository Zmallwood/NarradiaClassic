#include "shader_program_v.h"
#include "shader_program.h"

namespace Narradia
{
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
   auto ShaderProgramV::CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type)
       -> GLuint {
      *shader = glCreateShader(shader_type);
      glShaderSource(*shader, 1, &shader_src, NULL);
      glCompileShader(*shader);
      GLint shader_compiled = GL_FALSE;
      glGetShaderiv(*shader, GL_COMPILE_STATUS, &shader_compiled);
      return shader_compiled;
   }
}
