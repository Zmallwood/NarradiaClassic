#pragma once

namespace Narradia
{
   auto DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation = 0.0f,
       float scaling = 1.0f, float brightness = 1.0f, glm::vec3 color_mod = {1.0f, 1.0f, 1.0f},
       bool no_fog = false, bool no_lighting = false) -> void;
}
