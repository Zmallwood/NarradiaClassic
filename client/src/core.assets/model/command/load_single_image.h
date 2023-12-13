#pragma once
#include <GL/glew.h>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Loads single image with provided path, creating a GL texture and returning its GLuint
   /// id.
   ///
   /// @param[in] abs_file_path File path to image to load.
   /// @return GLuint id for loaded image.
   ////////////////////////////////////////////////////////////////////////////////
   auto LoadSingleImage(std::string_view abs_file_path) -> GLuint;
}
