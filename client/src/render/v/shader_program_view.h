#pragma once

#include "render/m/shader_program.h"

namespace Narradia
{
   class ShaderProgramView
   {
     public:
      ShaderProgramView()
          : shader_program_(std::make_shared<ShaderProgram>())
      {
      }
      bool Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src);

      auto shader_program()
      {
         return shader_program_;
      }

     private:
      std::shared_ptr<ShaderProgram> shader_program_;
   };
}
