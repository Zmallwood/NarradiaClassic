#pragma once

namespace Narradia
{
   typedef GLuint RenderID;
}

// clang-format off
#include "singleton.h"
#include "assets.h"
#include "core.h"
#include <GL/glew.h>
//clang-format on

namespace Narradia
{

   // Canvas utils
#if 1
   inline Size CanvasSize() {
      int w, h;
      SDL_GetWindowSize(Graphics::get()->win().get(), &w, &h);

      return {w, h};
   }
   inline float AspectRatio() {
      auto canv_sz = CanvasSize();

      return static_cast<float>(canv_sz.w) / canv_sz.h;
   }
   inline float WidthToHeight(float w) {
      return w * AspectRatio();
   }
   inline float HeightToWidth(float h) {
      return h / AspectRatio();
   }
#endif

   // Mouse, mouse and texture utils
#if 1
   inline PointF MousePosition() {
      int x_px, y_px;
      auto canv_sz = CanvasSize();
      SDL_GetMouseState(&x_px, &y_px);
      auto x = static_cast<float>(x_px) / canv_sz.w;
      auto y = static_cast<float>(y_px) / canv_sz.h;

      return {x, y};
   }
   inline std::string_view CurrTime() {
      char buffer[80];
      auto now = time(0);
      auto p_tstruct = localtime(&now);
      strftime(buffer, sizeof(buffer), "%X", p_tstruct);

      return std::string_view(buffer);
   }
   inline Size TextureDimensions(std::string_view img_name) {
      Size dim;
      int mip_level = 0;
      auto img_id = ImageBank::get()->GetImage(img_name);
      glBindTexture(GL_TEXTURE_2D, img_id);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);

      return dim;
   }
#endif

   // File utils
#if 1
   inline std::string_view FileExtension(std::string_view abs_path) {
      return abs_path.substr(abs_path.find_last_of('.') + 1);
   }
   inline std::string FileNameNoExt(std::string_view abs_path) {
      auto name_with_ext = abs_path.substr(abs_path.find_last_of('/') + 1);

      return std::string(name_with_ext.substr(0, name_with_ext.find_last_of('.')));
   }
#endif

// Singleton helpers
#if 1
   static std::vector<std::function<void()>> gDisposeActions;
   inline void AddSingletonDisposeAction(std::function<void()> action) {
      gDisposeActions.push_back(action);
   }
   inline void DisposeSingletons() {
      for (auto &action : gDisposeActions)
         action();
   }
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
