#pragma once

namespace Narradia
{
    void DrawImagePolygon(
        std::string_view image_name, RenderId vao_id, int vertex_count,
        bool depth_test_off = false);
}
