#pragma once
#include "pointf.h"
namespace Narradia {
  class Point3F {
   public:
    Point3F Translate(float dx, float dy, float dz);
    Point3F Multiply(float k);
    PointF GetXZ();

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
  };
}
