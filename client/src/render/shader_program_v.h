#pragma once

namespace Narradia
{
   class ShaderProgram;

   class ShaderProgramV
   {
     public:
      ShaderProgramV();
      bool Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src);
      auto shader_program()
      {
         return shader_program_;
      }

     private:
      std::shared_ptr<ShaderProgram> shader_program_;
   };
}
