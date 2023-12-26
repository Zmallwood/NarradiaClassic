#pragma once
#include <GL/glew.h>
namespace Narradia
{
   typedef GLuint RenderID;

   // Canvas utils
#if 1
   Size CanvasSize();

   float AspectRatio();

   float WidthToHeight(float w);

   float HeightToWidth(float h);
#endif

   // Mouse, time, and texture utils
#if 1
   PointF MousePosition();

   std::string_view CurrTime();

   Size TextureDimensions(std::string_view img_name);
#endif
}
