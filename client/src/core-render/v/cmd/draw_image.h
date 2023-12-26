#pragma once
#include "../../../core-assets/m/image_bank.h"
#include "../../../core-render/v/renderer_2d_images_view.h"
#include "../../m/renderer_base.h"
#include <vector>
namespace Narradia
{
   auto DrawImage(
       std::string_view image_name, RenderID rid, const RectF &dest, Color color = Colors::white)
       -> void;
}
