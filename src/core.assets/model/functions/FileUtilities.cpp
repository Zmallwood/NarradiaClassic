#include "FileUtilities.h"

namespace Narradia {
    /**
     * Gets file extension, without dot, for provided file path.
     */
    std::string_view GetFileExtension(std::string_view abs_file_path) {
        auto ext_pos = abs_file_path.find_last_of('.') + 1;
        auto file_ext = abs_file_path.substr(ext_pos);
        return file_ext;
    }

    /**
     * Gets file name without path or extension for provided file path.
     */
    std::string_view GetFileNameNoExt(std::string_view abs_file_path) {
        auto img_name_start = abs_file_path.find_last_of('/') + 1;
        auto img_name_with_ext = abs_file_path.substr(img_name_start);
        auto img_name_ext_pos = img_name_with_ext.find_last_of('.');
        auto file_name_no_ext = img_name_with_ext.substr(0, img_name_ext_pos);
        return file_name_no_ext;
    }
}
