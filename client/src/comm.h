#pragma once

namespace Narradia
{
   typedef GLuint RenderID;

// Matter
#if 1
   // Geometry
#if 1
   class Point {
     public:
      Point Translate(int dx, int dy) {

         return {x + dx, y + dy};
      }

      int x = 0;
      int y = 0;
   };

   class PointF {
     public:
      PointF Translate(float dx, float dy) const {

         return {x + dx, y + dy};
      }

      Point ToIntPoint() {

         return {static_cast<int>(x), static_cast<int>(y)};
      }

      float x = 0.0f;
      float y = 0.0f;
   };

   class Point3F {
     public:
      Point3F Translate(float dx, float dy, float dz) {

         return {x + dx, y + dy, z + dz};
      }

      Point3F Multiply(float k) {

         return {x * k, y * k, z * k};
      }

      PointF GetXZ() {
         return {x, z};
      }

      float x = 0.0f;
      float y = 0.0f;
      float z = 0.0f;
   };

   class Size {
     public:
      int w = 0;
      int h = 0;
   };

   class SizeF {
     public:
      float w = 0.0f;
      float h = 0.0f;
   };

   class GLRectF {
     public:
      float x = .0f;
      float y = .0f;
      float w = .0f;
      float h = .0f;
   };

   class RectF {
     public:
      GLRectF ToGLRectF() const {

         return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
      }

      RectF Translate(float dx, float dy) const {

         return {x + dx, y + dy, w, h};
      }

      PointF GetPosition() const {

         return {x, y};
      }

      PointF GetCenter() const {

         return {x + w / 2, y + h / 2};
      }

      bool Contains(PointF point) const {

         return point.x >= x && point.y >= y && point.x < x + w && point.y < y + h;
      }

      RectF WithWidth(float w_new) const {

         return {x, y, w_new, h};
      }

      SizeF GetSize() const {

         return {w, h};
      }

      float x = 0.0f;
      float y = 0.0f;
      float w = 0.0f;
      float h = 0.0f;
   };
#endif

   // Colors
#if 1
   class Color {
     public:
      SDL_Color ToSDLColor() const {

         return {
             static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255),
             static_cast<unsigned char>(b * 255), static_cast<unsigned char>(a * 255)};
      }

      float r = 1.0f;
      float g = 1.0f;
      float b = 1.0f;
      float a = 1.0f;
   };

   namespace Colors
   {
      inline static Color wheat = {1.0f, 1.0f, 0.8f, 1.0f};
      inline static Color mild_blue = {0.0f, 0.5f, 1.0f, 1.0f};
      inline static Color black = {0.0f, 0.0f, 0.0f, 1.0f};
      inline static Color white = {1.0f, 1.0f, 1.0f, 1.0f};
      inline static Color purple = {0.5f, 0.3f, 0.8, 1.0f};
      inline static Color red = {1.0f, 0.0f, 0.0, 1.0f};
      inline static Color yellow = {1.0f, 1.0f, 0.0, 1.0f};
      inline static Color dark_gray = {0.3f, 0.3f, 0.3, 1.0f};
      inline static Color sky_blue = {0.3f, 0.4f, 0.6f, 1.0f};
   }
#endif

   // Vertices
#if 1
   class Vertex2F {
     public:
      PointF pos;
      Color color;
      PointF uv;
   };

   class Vertex3F {
     public:
      Point3F pos;
      Color color;
      PointF uv;
      Point3F normal;
   };
#endif
#endif

   // Singleton
#if 1
   template <class T>
   class Singleton {
     public:
      template <typename... U>
      static void Touch(U... args);
      static void Dispose();
      inline static std::shared_ptr<T> get();

     private:
      inline static std::shared_ptr<T> instance_;
   };

   // Function definitions
#if 1
   template <class T>
   template <class... __Args>
   void Singleton<T>::Touch(__Args... args) {

      if (!instance_) {

         instance_ = std::make_shared<T>(args...);
         AddSingletonDisposeAction([&] { instance_.reset(); });
      }
   }

   template <class T>
   void Singleton<T>::Dispose() {

      if (instance_) {

         instance_.reset();
         instance_ = nullptr;
      }
   }

   template <class T>
   std::shared_ptr<T> Singleton<T>::get() {

      if (!instance_)
         Touch();

      return instance_;
   }

#endif

   // Aliases
#if 1
   template <class T>
   using S = Singleton<T>;

   using String = std::string;

   using StringView = std::string_view;

   template <class T>
   using Vec = std::vector<T>;

   template <class T>
   using SharedPtr = std::shared_ptr<T>;

   template <class T, class U>
   using Map = std::map<T, U>;

   template <class T>
   using Set = std::set<T>;

   template <class T>
   using Function = std::function<T>;

   using Exception = std::exception;

   template <class T, class... __Args>
   auto MakeShared(__Args... args) {
      return std::make_shared<T>(args...);
   }

   template <class T>
   inline auto ToString(T arg) {
      return std::to_string(arg);
   }
#endif

#endif

   // File utils
#if 1
   inline StringView FileExtension(StringView abs_path) {

      return abs_path.substr(abs_path.find_last_of('.') + 1);
   }

   inline String FileNameNoExt(StringView abs_path) {

      auto name_with_ext = abs_path.substr(abs_path.find_last_of('/') + 1);

      return String(name_with_ext.substr(0, name_with_ext.find_last_of('.')));
   }
#endif
}

// clang-format off
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

      return StringView(buffer);
   }

   inline Size TextureDimensions(StringView img_name) {

      Size dim;
      int mip_level = 0;
      auto img_id = ImageBank::get()->GetImage(img_name);

      glBindTexture(GL_TEXTURE_2D, img_id);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);

      return dim;
   }
#endif


// Singleton helpers
#if 1
   static Vec<Function<void()>> gDisposeActions;

   inline void AddSingletonDisposeAction(Function<void()> action) {

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
