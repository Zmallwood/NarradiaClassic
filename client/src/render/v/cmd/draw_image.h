#pragma once

#include "assets/m/image_bank.h"
#include "render/v/renderer_2d_images_view.h"
#include "render/m/renderer_base.h"

namespace Narradia
{
   auto DrawImage(
       std::string_view image_name, RenderID rid, const RectF &dest, Color color = Colors::white)
       -> void;
}
