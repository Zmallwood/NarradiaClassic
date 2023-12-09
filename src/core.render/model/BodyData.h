#pragma once

namespace Narradia {
    class BodyData {
      public:
        RenderID rid = -1;
        int num_vertices = 0;
        std::string_view image_name;
    };
}
