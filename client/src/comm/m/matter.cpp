#include "matter.h"
namespace Narradia
{
   Point Point::Translate(int dx, int dy)
   {
      return {x + dx, y + dy};
   }

   PointF PointF::Translate(float dx, float dy) const
   {
      return {x + dx, y + dy};
   }

   Point PointF::ToIntPoint()
   {
      return {static_cast<int>(x), static_cast<int>(y)};
   }

   Point3F Point3F::Translate(float dx, float dy, float dz)
   {
      return {x + dx, y + dy, z + dz};
   }

   Point3F Point3F::Multiply(float k)
   {
      return {x * k, y * k, z * k};
   }

   PointF Point3F::GetXZ()
   {
      return {x, z};
   }

   GLRectF RectF::ToGLRectF() const
   {
      return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
   }

   RectF RectF::Translate(float dx, float dy) const
   {
      return {x + dx, y + dy, w, h};
   }

   PointF RectF::GetPosition() const
   {
      return {x, y};
   }

   PointF RectF::GetCenter() const
   {
      return {x + w / 2, y + h / 2};
   }

   bool RectF::Contains(PointF point) const
   {
      return point.x >= x && point.y >= y && point.x < x + w && point.y < y + h;
   }

   RectF RectF::WithWidth(float w_new) const
   {
      return {x, y, w_new, h};
   }

   SizeF RectF::GetSize() const
   {
      return {w, h};
   }

   SDL_Color Color::ToSDLColor() const
   {
      return {
          static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255),
          static_cast<unsigned char>(b * 255), static_cast<unsigned char>(a * 255)};
   }
}
