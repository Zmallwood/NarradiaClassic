#pragma once
#include "color.h"
#include "pointf.h"

namespace Narradia {
  /**
   Used to describe objects for 2D rendering.
  */
  class Vertex2F {
   public:
    PointF position;
    Color color;
    PointF uv;
  };
}
