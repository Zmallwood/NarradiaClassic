#include "File_Utilities.h"

namespace Narradia {

    String_View FileExtension(String_View abs_path) {

        return abs_path.substr(abs_path.find_last_of('.') + 1);
    }

    String FileNameNoExt(String_View abs_path) {

        auto name_with_ext = abs_path.substr(abs_path.find_last_of('/') + 1);
        return String(name_with_ext.substr(0, name_with_ext.find_last_of('.')));
    }
}
