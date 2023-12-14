#pragma once
#include <GL/glew.h>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Compiles shader, fragment or vertex type, and returns success status.
   ///
   /// @param[in] shader_src Shader source code.
   /// @param[out] shader Will be stored with the resulting shader ID.
   /// @param[in] shader_type Type of shader, vertex or fragment.
   /// @return Success status.
   ////////////////////////////////////////////////////////////////////////////////
   auto CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) -> GLuint;
}
