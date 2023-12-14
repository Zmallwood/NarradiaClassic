#pragma once
#include "color.h"
#include "point3f.h"
#include "pointf.h"
namespace Narradia
{
   class Vertex3F {
     public:
      Point3F position;
      Color color;
      PointF uv;
      Point3F normal;
   };
}
