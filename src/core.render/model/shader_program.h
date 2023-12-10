#pragma once
#include <GL/glew.h>

namespace Narradia {
  /**
   Simple holding class for an OpenGL program, of which
   every Renderer has one.
  */
  class ShaderProgram {
   public:
    void Cleanup();

    auto program_id() const {
      return program_id_;
    }

    void set_program_id(GLuint value) {
      program_id_ = value;
    }

   private:
    GLuint program_id_ = 0;
  };
}