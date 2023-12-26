#pragma once
#include "gl_rectf.h"
#include "pointf.h"
#include "sizef.h"
namespace Narradia
{
   /**
    Floating point type rectangle.
   */
   class RectF
   {
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
}
