#pragma once
#include "PointF.h"
#include "Color.h"

namespace Narradia {
    /**
     * Used to describe objects for 2D rendering.
     */
    class Vertex2F {
      public:
        PointF position;
        Color color;
        PointF uv;
    };
}
