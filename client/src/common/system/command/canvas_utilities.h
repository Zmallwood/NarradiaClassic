#pragma once
#include "../../../matter/model/size.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Returns canvas size.
   ///
   /// @return Canvas size in pixels.
   ////////////////////////////////////////////////////////////////////////////////

   auto CanvasSize() -> Size;

   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Gets aspect ratio of canvas.
   ///
   /// @return Aspect ratio (w/h)
   ////////////////////////////////////////////////////////////////////////////////
   auto AspectRatio() -> float;
}
