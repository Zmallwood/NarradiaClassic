#include "FileUtilities.h"

namespace Narradia {
    std::string_view GetFileExtension(std::string_view abs_file_path) {
        auto extPos = abs_file_path.find_last_of('.') + 1;
        auto fileExt = abs_file_path.substr(extPos);
        
        return fileExt;
    }

    std::string_view GetFileNameNoExt(std::string_view abs_file_path) {
        auto imgNameStart = abs_file_path.find_last_of('/') + 1;
        auto imgNameWithExt = abs_file_path.substr(imgNameStart);
        auto imgNameExtPos = imgNameWithExt.find_last_of('.');
        auto fileNameNoExt = imgNameWithExt.substr(0, imgNameExtPos);

        return fileNameNoExt;
    }
}