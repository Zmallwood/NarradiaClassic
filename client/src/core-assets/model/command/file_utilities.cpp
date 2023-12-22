#include "file_utilities.h"
namespace Narradia
{
   auto FileExtension(std::string_view abs_path) -> std::string_view {
      return abs_path.substr(abs_path.find_last_of('.') + 1);
   }

   auto FileNameNoExt(std::string_view abs_path) -> std::string {
      auto name_with_ext = abs_path.substr(abs_path.find_last_of('/') + 1);
      return std::string(name_with_ext.substr(0, name_with_ext.find_last_of('.')));
   }
}
