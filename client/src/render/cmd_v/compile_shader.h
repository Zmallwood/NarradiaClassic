#pragma once

namespace Narradia
{
   auto CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) -> GLuint;
}
