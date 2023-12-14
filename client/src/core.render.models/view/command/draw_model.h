#pragma once
#include "../renderer_models_view.h"
#include "../../../core.render/view/camera_gl.h"
#include "../../../conf/model/conf.h"
#include "../../../core.assets/model/model_bank.h"
#include "../../../core.assets/model/image_bank.h"
namespace Narradia
{
   void DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation = 0.0f,
       float scaling = 1.0f, float brightness = 1.0f, glm::vec3 color_mod = {1.0f, 1.0f, 1.0f},
       bool no_fog = false, bool no_lighting = false);
}
