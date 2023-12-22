#include "rectf.h"
namespace Narradia
{
   /**
    Returns this object as a GLRectF type, which is in the
    OpenGL coordinate system.
   */
   GLRectF RectF::ToGLRectF() const {
      return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
   }

   /**
    Returns a translated copy of this object, while not
    modifying this one.
   */
   RectF RectF::Translate(float dx, float dy) const {
      return {x + dx, y + dy, w, h};
   }

   /**
    Returns only the position part of this rectangle.
   */
   PointF RectF::GetPosition() const {
      return {x, y};
   }

   /**
    Returns the center point of this rectangle.
   */
   PointF RectF::GetCenter() const {
      return {x + w / 2, y + h / 2};
   }

   /**
    Tells if this rectangle has a point within its
    boundaries.
   */
   bool RectF::Contains(PointF point) const {
      return point.x >= x && point.y >= y && point.x < x + w && point.y < y + h;
   }

   RectF RectF::WithWidth(float w_new) const {
      return {x, y, w_new, h};
   }

   SizeF RectF::GetSize() const {
      return {w, h};
   }
}
