#pragma once

#include "singleton.h"
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

   // Singleton helpers
#if 1
   void AddSingletonDisposeAction(std::function<void()> action);
   void DisposeSingletons();
#endif

   // Misc
#if 1
   template <class T>
   class Square {
     public:
      void SetAll(T value) {
         _00 = value;
         _01 = value;
         _11 = value;
         _10 = value;
      }

      T _00;
      T _01;
      T _11;
      T _10;
   };
#endif
}
