#include "FileUtilities.h"

namespace Narradia {
   StringView FileExtension(StringView _absPath) {
      return _absPath.substr(_absPath.find_last_of('.') + 1);
   }
   String FileNameNoExt(StringView _absPath) {
      auto _nameWithExt = _absPath.substr(_absPath.find_last_of('/') + 1);
      return String(_nameWithExt.substr(0, _nameWithExt.find_last_of('.')));
   }
}
