#include "file_utilities.h"
namespace Narradia
{
   std::string_view FileExtension(std::string_view abs_path)
   {
      return abs_path.substr(abs_path.find_last_of('.') + 1);
   }

   std::string FileNameNoExt(std::string_view abs_path)
   {
      auto name_with_ext = abs_path.substr(abs_path.find_last_of('/') + 1);
      return std::string(name_with_ext.substr(0, name_with_ext.find_last_of('.')));
   }
}
