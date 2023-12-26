#pragma once
#include "../../../core-assets/m/image_bank.h"
#include "../../../core-render/v/renderer_2d_images_view.h"
#include "../../../matter/m/color.h"
#include "../../../matter/m/colors.h"
#include "../../m/renderer_base.h"
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders an image to the canvas, must previously have been initialized with NewImage().
   ///
   /// @param[in] image_name Image name.
   /// @param[in] rid RID from NewImage().
   /// @param[in] dest Destination rectangle on canvas.
   /// @param[in] color Color to render the image with.
   ////////////////////////////////////////////////////////////////////////////////
   auto DrawImage(
       std::string_view image_name, RenderID rid, const RectF &dest, Color color = Colors::white)
       -> void;
}
