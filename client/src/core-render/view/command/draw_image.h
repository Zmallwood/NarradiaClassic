#pragma once
#include "../../../common/system/typedefs.h"
#include "../../../core-assets/model/image_bank.h"
#include "../../../core-render/view/renderer_2d_images_view.h"
#include "../../../matter/model/color.h"
#include "../../../matter/model/colors.h"
#include "../../model/renderer_base.h"
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
