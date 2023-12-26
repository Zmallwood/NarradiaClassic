#pragma once
#include <string>
namespace Narradia
{
   std::string_view FileExtension(std::string_view abs_path);

   std::string FileNameNoExt(std::string_view abs_path);
}
