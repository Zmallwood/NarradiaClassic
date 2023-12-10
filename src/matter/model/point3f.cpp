#include "point3f.h"
namespace Narradia {
  Point3F Point3F::Translate(float dx, float dy, float dz) {
    return {x + dx, y + dy, z + dz};
  }

  Point3F Point3F::Multiply(float k) {
    return {x * k, y * k, z * k};
  }

  PointF Point3F::GetXZ() {
    return {x, z};
  }
}
