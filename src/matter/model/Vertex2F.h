#pragma once
#include "PointF.h"
#include "Color.h"

namespace Narradia {
    class Vertex2F {
      public:
        PointF position;
        Color color;
        PointF uv;
    };
}
