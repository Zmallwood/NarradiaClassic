#pragma once
#include <GL/glew.h>
#include <string_view>
namespace Narradia
{
   auto LoadSingleImage(std::string_view abs_file_path) -> GLuint;
}
