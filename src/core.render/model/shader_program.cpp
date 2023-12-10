#include "shader_program.h"

namespace Narradia {
  /**
   Delete shader program when no longer used.
  */
  void ShaderProgram::Cleanup() {
    glDeleteProgram(program_id_);
  }
}
