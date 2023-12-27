#pragma once

namespace Narradia
{
   auto DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off = false) -> void;
}
