#pragma once
#include "GLRectF.h"
#include "PointF.h"

namespace Narradia {
    /**
     * Floating point type rectangle.
     */
    class RectF {
      public:
        GLRectF ToGLRectF() const;

        RectF Translate(float dx, float dy) const;

        PointF GetPosition() const;

        PointF GetCenter() const;

        bool Contains(PointF point) const;

        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };
}
