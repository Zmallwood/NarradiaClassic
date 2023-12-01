#pragma once

namespace Narradia {
    class ImageEntry {
      public:
        std::string_view file_name;
        GLuint texture_id;
    };
}
