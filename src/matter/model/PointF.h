#pragma once

namespace Narradia {
    /**
     * Floating point type 2D point.
     */
    class PointF {
      public:
        PointF Translate(float dx, float dy) const;

        float x = 0.0f;
        float y = 0.0f;
    };
}
