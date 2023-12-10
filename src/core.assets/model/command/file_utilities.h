#pragma once

namespace Narradia {
  std::string_view GetFileExtension(std::string_view abs_file_path);
  std::string_view GetFileNameNoExt(std::string_view abs_file_path);
}
