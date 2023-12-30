#pragma once

struct SDL_Color;

namespace Narradia
{
   // Geometry
#if 1
   class Point {
     public:
      Point Translate(int dx, int dy);

      int x = 0;
      int y = 0;
   };

   class PointF {
     public:
      PointF Translate(float dx, float dy) const;
      Point ToIntPoint();

      float x = 0.0f;
      float y = 0.0f;
   };

   class Point3F {
     public:
      Point3F Translate(float dx, float dy, float dz);
      Point3F Multiply(float k);
      PointF GetXZ();

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
      GLRectF ToGLRectF() const;
      RectF Translate(float dx, float dy) const;
      PointF GetPosition() const;
      PointF GetCenter() const;
      bool Contains(PointF point) const;
      RectF WithWidth(float w_new) const;
      SizeF GetSize() const;

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
      SDL_Color ToSDLColor() const;

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
}
