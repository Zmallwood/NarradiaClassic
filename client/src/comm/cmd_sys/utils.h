#pragma once

#include "comm/singleton_sys.h"
#include <GL/glew.h>

namespace Narradia
{
   typedef GLuint RenderID;

   template <class T>
   using S = Singleton<T>;

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

   // File utils
#if 1
   std::string_view FileExtension(std::string_view abs_path);

   std::string FileNameNoExt(std::string_view abs_path);
#endif
}
