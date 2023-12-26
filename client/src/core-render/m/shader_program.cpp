#include "shader_program.h"
namespace Narradia
{
   void ShaderProgram::Cleanup()
   {
      glDeleteProgram(program_id_);
   }
}
